#include "car_config.hpp"
#include "components/car_component.hpp"

float car_config::get_price() const {
    float result = 0;
    for(auto *component : components) {
        result += component->get_price();
    }
    return result;
}
