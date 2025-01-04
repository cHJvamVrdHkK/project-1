#ifndef CAR_COLOR_HPP
#define CAR_COLOR_HPP

#include "car_component.hpp"

class car_color : public car_component {
public:
    explicit car_color(std::string name, float price)
        : car_component(name, price) {}

    std::string get_details() const;
    float get_price() const;

private:
};

#endif //CAR_COLOR_HPP
