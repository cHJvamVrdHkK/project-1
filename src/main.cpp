#include "program.hpp"

#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include <d3d11.h>
#include <tchar.h>

#pragma comment(lib, "d3d11")

static ID3D11Device *d3d11_device;
static ID3D11DeviceContext *d3d11_device_context;
static IDXGISwapChain *dxgi_swap_chain;
static UINT resize_width, resize_height;
static ID3D11RenderTargetView *d3d11_render_target_view;

LRESULT WINAPI WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main(int argc, char **argv) {
    program::init();

    // Create and register a window class
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = L"HelloSailor";

    RegisterClassExW(&wc);

    // Create window
    DWORD style = WS_OVERLAPPEDWINDOW|WS_SIZEBOX;

    HWND hwnd = CreateWindowW(
        wc.lpszClassName, L"Konfigurator", style,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        0, 0, wc.hInstance, 0);

    // Create D3D11 device, context and DXGI swap chain
    {
        // Default 0 value for Width and Height means to get it from HWND automatically
        DXGI_SWAP_CHAIN_DESC desc = {};
        desc.BufferCount = 2;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BufferDesc.RefreshRate.Numerator = 60;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.OutputWindow = hwnd;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.Windowed = TRUE;
        // Windows 10 allows to use DXGI_SWAP_EFFECT_FLIP_DISCARD
        // For Windows 8 compatibility use DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL
        // For Windows 7 compatibility use DXGI_SWAP_EFFECT_DISCARD
        desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0 };

        HRESULT result = D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0,
                0, feature_levels, 1, D3D11_SDK_VERSION, &desc, &dxgi_swap_chain,
                &d3d11_device, 0, &d3d11_device_context);
        if (result == DXGI_ERROR_UNSUPPORTED) {
            result = D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_WARP, 0,
                    0, feature_levels, 1, D3D11_SDK_VERSION, &desc, &dxgi_swap_chain,
                    &d3d11_device, 0, &d3d11_device_context);
        }

        assert(SUCCEEDED(result));
    }

    // Show the window
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(d3d11_device, d3d11_device_context);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    for(bool done = false; !done;) {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                done = true;
            }
        }

        if (done)
            break;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (resize_width != 0 && resize_height != 0) {
            if (d3d11_render_target_view) {
                d3d11_render_target_view->Release();
                d3d11_render_target_view = 0;
            }

            dxgi_swap_chain->ResizeBuffers(0, resize_width, resize_height, DXGI_FORMAT_UNKNOWN, 0);
            resize_width = resize_height = 0;

            ID3D11Texture2D *frame_buffer = 0;
            dxgi_swap_chain->GetBuffer(0, IID_PPV_ARGS(&frame_buffer));
            d3d11_device->CreateRenderTargetView(frame_buffer, 0, &d3d11_render_target_view);
            frame_buffer->Release();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        program::update();

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        d3d11_device_context->OMSetRenderTargets(1, &d3d11_render_target_view, nullptr);
        d3d11_device_context->ClearRenderTargetView(d3d11_render_target_view, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        dxgi_swap_chain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
                return 0;
            resize_width = (UINT)LOWORD(lParam); // Queue resize
            resize_height = (UINT)HIWORD(lParam);
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}
