#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "components.hpp"

#include <vector>
#include <array>

class program {
public:
    static void load_models();
    static void update();

    static float get_config_price();

    static std::string models_path;
    static std::string config_path;
    static std::vector<components::model *> car_models;
    static std::array<car_component *, 4> selected_components;
};

#endif //PROGRAM_HPP
