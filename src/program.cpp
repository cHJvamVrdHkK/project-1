#include "program.hpp"

#include "imgui/imgui.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <windows.h>

std::string program::models_path;
std::string program::config_path;
std::vector<components::model *> program::car_models;
std::array<car_component *, 4> program::selected_components;

static bool car_component_getter(void* data, int idx, const char** out_text) {
    auto *vec = reinterpret_cast<std::vector<car_component *> *>(data);
    if(idx < 0 || idx >= vec->size()) {
        return false;
    }

    *out_text = vec->at(idx)->get_name().c_str();
    return true;
}

void program::load_models() {
    std::ifstream file(program::models_path);

    components::model *current_model = 0;
    std::string line;
    for(int line_number = 1; std::getline(file, line); ++line_number) {
        if(line.empty()) continue;

        std::istringstream stream(line);

        std::string command;
        stream >> command;

        if(command == "model") {
            std::string name, desc;
            float price;
            stream >> std::quoted(name) >> price >> std::quoted(desc);

            program::car_models.push_back(
                    current_model = new components::model(name, price, desc));
        } else {
            if(current_model) {
                std::string name;
                float price;
                stream >> std::quoted(name) >> price;

                if(command == "engine") {
                    std::string kind_, gear_kind_;
                    stream >> kind_ >> gear_kind_;

                    components::engine::engine_kind kind = components::engine::engine_kind_from_string(kind_);
                    if(kind == components::engine::engine_kind::Invalid) {
                        std::cerr << "Error in line " << line_number << ": Engine kind '" << kind_ << "' is not supported.\n";
                        continue;
                    }

                    components::engine::gear_box_kind gear_kind = components::engine::gear_box_kind_from_string(gear_kind_);
                    if(gear_kind == components::engine::gear_box_kind::Invalid) {
                        std::cerr << "Error in line " << line_number << ": Gear box kind '" << gear_kind_ << "' is not supported.\n";
                        continue;
                    }

                    current_model->add_component(new components::engine(name, price, kind, gear_kind));
                } else if(command == "color") {
                    current_model->add_component(new components::color(name, price));
                } else if(command == "wheels") {
                    int radius;
                    stream >> radius;

                    current_model->add_component(new components::wheels(name, price, radius));
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

float program::get_config_price() {
    float result = 0;
    for(auto *component : selected_components)
        result += component->get_price();
    return result;
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
                selected_components[0] = model;

                auto engines = model->get_components<components::engine>();
                ImGui::Combo("Silnik", &item_current_2, car_component_getter, (void *)&engines, engines.size());
                selected_components[1] = engines[item_current_2];

                auto colors = model->get_components<components::color>();
                ImGui::Combo("Kolor", &item_current_3, car_component_getter, (void *)&colors, colors.size());
                selected_components[2] = colors[item_current_3];

                auto wheels = model->get_components<components::wheels>();
                ImGui::Combo("Obrecze", &item_current_4, car_component_getter, (void *)&wheels, wheels.size());
                selected_components[3] = wheels[item_current_4];
            }
            ImGui::EndChild();
        }

        ImGui::SameLine();

        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("ChildR", ImVec2(0, 0), ImGuiChildFlags_Borders, window_flags);
            {
                static char const *separators[] = {"Model", "Silnik", "Kolor", "Obrecze"};
                for(auto i = 0; i < selected_components.size(); ++i) {
                    auto *component = selected_components[i];

                    ImGui::SeparatorText(separators[i]);

                    ImGui::Text("%s", component->get_name().c_str());
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1, 0, 1, 1), "%.2f PLN", component->get_price());

                    ImGui::TextWrapped("%s", component->get_details().c_str());
                }

                ImGui::Text("Cena:");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.2f", get_config_price());

                if(ImGui::Button("Zapisz")) {
                    std::ofstream out(config_path);
                    for(auto i = 0; i < selected_components.size(); ++i) {
                        auto *component = selected_components[i];
                        out << separators[i] << ": " << component->get_name() << '\n';
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
