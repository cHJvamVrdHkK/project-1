#ifndef CAR_WHEELS_HPP
#define CAR_WHEELS_HPP

#include "car_component.hpp"

class car_wheels : public car_component {
public:
    car_wheels() = default;
    car_wheels(std::string name, float radius)
        : car_component(name, 100), radius(radius) {}

    std::string get_details() const;
    unsigned int calculate_price() const;

private:
    float radius;
};

#endif //CAR_WHEELS_HPP
