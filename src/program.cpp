#include "program.hpp"

#include "car_config.hpp"
#include "components/car_model.hpp"
#include "components/car_engine.hpp"
#include "components/car_color.hpp"
#include "components/car_wheels.hpp"

#include "imgui/imgui.h"

#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>
#include <iomanip>

#include <windows.h>

std::vector<car_model *> program::car_models;
car_config program::config;
std::string program::models_path;
std::string program::config_path;

static void init_models() {
    std::ifstream file(program::models_path);

    car_model *current_model = 0;
    std::string line;
    for(int line_number = 1; std::getline(file, line); ++line_number) {
        if(line.empty()) continue;

        std::istringstream stream(line);

        std::string command;
        stream >> command;

        if(command == "model") {
            std::string name;
            float price;
            stream >> std::quoted(name) >> price;

            program::car_models.push_back(
                    current_model = new car_model(name, price));
        } else {
            // NOTE: Check if model command was used and current_model exists so that it can be configured.
            if(current_model) {
                std::string name;
                float price;
                stream >> std::quoted(name) >> price;

                if(command == "engine") {
                    std::string kind_, gear_kind_;
                    stream >> kind_ >> gear_kind_;

                    engine_kind kind = engine_kind_from_string(kind_);
                    if(kind == engine_kind::Invalid) {
                        std::cerr << "Error in line " << line_number << ": Engine kind '" << kind_ << "' is not supported.\n";
                        continue;
                    }

                    gear_box_kind gear_kind = gear_box_kind_from_string(gear_kind_);
                    if(gear_kind == gear_box_kind::Invalid) {
                        std::cerr << "Error in line " << line_number << ": Gear box kind '" << gear_kind_ << "' is not supported.\n";
                        continue;
                    }

                    current_model->add_component(new car_engine(name, price, kind, gear_kind));
                } else if(command == "color") {
                    float r, g, b;
                    stream >> r >> g >> b;

                    current_model->add_component(new car_color(name, price));
                } else if(command == "wheels") {
                    int radius;
                    stream >> radius;

                    current_model->add_component(new car_wheels(name, price, radius));
                } else {
                    std::cerr << "Error in line " << line_number << ": Command '" << command << "' doesn't exist.\n";
                    continue;
                }
            } else {
                std::cerr << "Error in line " << line_number << ": trying to add car's components to a model, but haven't started any model yet.\n";
                continue;
            }
        }
    }

    file.close();
}

void save_config(std::ofstream &file, car_config *config) {
}

template<typename T>
T *select_component(car_model *selected_model) {
    auto components = selected_model->get_components<T>();
    for(size_t i = 0; i < components.size(); ++i) {
        std::cout << i+1 << ". " << components[i]->get_name() << '\n';
    }

    int n = 0;
    while(n <= 0 || n > components.size()) {
        std::cout << ">> " << std::flush;
        std::cin >> n;
    }

    return components[n-1];
}

std::string chop_last_slash(std::string const &str) {
    size_t pos = str.find_last_of("\\/");
    if (pos != std::string::npos) {
        return str.substr(0, pos);
    }
    return str;
}

std::string get_binary_path() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(0, buffer, MAX_PATH);

    std::string const result(buffer);
    return chop_last_slash(result);
}

void program::init() {
    std::string local_binary_path = get_binary_path();
    std::string parent_binary_path = chop_last_slash(local_binary_path);
    std::string parent_data_path = parent_binary_path + "/data";

    models_path = parent_data_path + "/models";
    config_path = parent_data_path + "/config";

    init_models();
}

bool car_component_getter(void* data, int idx, const char** out_text) {
    auto *vec = reinterpret_cast<std::vector<car_component *> *>(data);
    if(idx < 0 || idx >= vec->size()) {
        return false;
    }

    *out_text = vec->at(idx)->get_name().c_str();
    return true;
}

void program::update() {

    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

    ImGuiViewport const *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    static int item_current_1 = 0;
    static int item_current_2 = 0;
    static int item_current_3 = 0;
    static int item_current_4 = 0;

    if (ImGui::Begin("Main", 0, flags))
    {
        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
            ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0), ImGuiChildFlags_None, window_flags);
            {
                if(ImGui::Combo("Model", &item_current_1, car_component_getter, (void *)&car_models, car_models.size())) {
                    item_current_2 = item_current_3 = item_current_4 = 0;
                }
                auto *model = car_models[item_current_1];
                config.components[0] = model;

                auto engines = model->get_components<car_engine>();
                ImGui::Combo("Silnik", &item_current_2, car_component_getter, (void *)&engines, engines.size());
                config.components[1] = engines[item_current_2];

                auto colors = model->get_components<car_color>();
                ImGui::Combo("Kolor", &item_current_3, car_component_getter, (void *)&colors, colors.size());
                config.components[2] = colors[item_current_3];

                auto wheels = model->get_components<car_wheels>();
                ImGui::Combo("Kola", &item_current_4, car_component_getter, (void *)&wheels, wheels.size());
                config.components[3] = wheels[item_current_4];
            }
            ImGui::EndChild();
        }

        ImGui::SameLine();

        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("ChildR", ImVec2(0, 0), ImGuiChildFlags_Borders, window_flags);
            {
                static char const *separators[] = {"Model", "Silnik", "Kolor", "Kola"};
                for(auto i = 0; i < config.components.size(); ++i) {
                    auto *component = config.components[i];

                    ImGui::SeparatorText(separators[i]);

                    ImGui::Text("%s", component->get_name().c_str());
                    ImGui::SameLine();
                    //std::cout << ImGui::GetContentRegionAvail().x;
                    ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.2f PLN", component->get_price());
                }

                ImGui::Dummy(ImVec2(0.0f, 10.0f));

                ImGui::Text("Cena: ");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.2f", config.get_price());

                if(ImGui::Button("Zapisz")) {
                    std::ofstream out(config_path);
                    for(auto *component : config.components) {
                        out << component->get_details();
                    }
                    out.close();
                }
            }
            ImGui::EndChild();

            ImGui::PopStyleVar();
        }
    }
    ImGui::End();
}
