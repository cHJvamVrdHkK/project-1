#ifndef CAR_CONFIG_HPP
#define CAR_CONFIG_HPP

#include <array>

class car_component;

struct car_config {
    float get_price() const;

    std::array<car_component *, 4> components;
};

#endif //CAR_CONFIG_HPP
