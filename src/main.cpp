#include "program.hpp"

#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include <d3d11.h>

#pragma comment(lib, "d3d11")

static ID3D11Device *d3d11_device;
static ID3D11DeviceContext *d3d11_device_context;
static IDXGISwapChain *dxgi_swap_chain;
static UINT resize_width, resize_height;
static ID3D11RenderTargetView *d3d11_render_target_view;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI window_proc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (ImGui_ImplWin32_WndProcHandler(window, msg, wparam, lparam))
        return true;

    LRESULT result = 0;
    switch (msg) {
        case WM_SIZE: {
            if (wparam == SIZE_MINIMIZED)
                break;
            resize_width = (UINT)LOWORD(lparam);
            resize_height = (UINT)HIWORD(lparam);
        } break;

        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;

        default: {
            result = DefWindowProcW(window, msg, wparam, lparam);
        } break;
    }
    return result;
}

static std::string chop_last_slash(std::string const &str) {
    size_t pos = str.find_last_of("\\/");
    if (pos != std::string::npos) {
        return str.substr(0, pos);
    }
    return str;
}

static std::string get_binary_path() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(0, buffer, MAX_PATH);

    std::string const result(buffer);
    return chop_last_slash(result);
}

static HWND create_output_window() {
    WNDCLASSEXW window_class = {};

    window_class.cbSize = sizeof(window_class);
    window_class.lpfnWndProc = &window_proc;
    window_class.hInstance = GetModuleHandleW(0);
    window_class.hIcon = LoadIconA(0, IDI_APPLICATION);
    window_class.hCursor = LoadCursorA(0, IDC_ARROW);
    window_class.lpszClassName = L"ConfiguratorClass";

    HWND result = 0;
    if(RegisterClassExW(&window_class))
    {
        DWORD style = WS_OVERLAPPEDWINDOW|WS_SIZEBOX;

        result = CreateWindowW(
                window_class.lpszClassName, L"konfigurator", style,
                CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
                0, 0, window_class.hInstance, 0);
    }

    return result;
}

int main(int argc, char **argv) {
    std::string local_binary_path = get_binary_path();
    std::string parent_binary_path = chop_last_slash(local_binary_path);
    std::string parent_data_path = parent_binary_path + "/data";

    program::models_path = parent_data_path + "/models";
    program::config_path = parent_data_path + "/config";

    program::load_models();

    HWND window = create_output_window();

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
        desc.OutputWindow = window;
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
    }

    // Show the window
    ShowWindow(window, SW_SHOWDEFAULT);
    UpdateWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(window);
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

