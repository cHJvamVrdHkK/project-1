#ifndef CAR_CONFIG_HPP
#define CAR_CONFIG_HPP

#include "components/car_component.hpp"

#include <string>
#include <array>

class car_model;
class car_component;

struct car_config {
    car_model *model;
    std::array<car_component *, 3> components;

    unsigned int get_price() const {
        unsigned int result = 0;
        for(auto *component : components) {
            result += component->calculate_price();
        }
        return result;
    }
};

#endif //CAR_CONFIG_HPP
