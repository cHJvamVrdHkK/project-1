#ifndef CAR_WHEELS_HPP
#define CAR_WHEELS_HPP

#include "car_component.hpp"

class car_wheels : public car_component {
public:
    car_wheels() = default;
    car_wheels(std::string name, float price, float radius)
        : car_component(name, price), radius(radius) {}

    std::string get_details() const;
    float get_price() const;

private:
    float radius;
};

#endif //CAR_WHEELS_HPP
