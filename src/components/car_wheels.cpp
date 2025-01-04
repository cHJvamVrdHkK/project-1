#include "car_wheels.hpp"

#include <sstream>

std::string car_wheels::get_details() const {
    std::stringstream ss;
    ss << radius << "-calowe";

    return ss.str();
}

float car_wheels::get_price() const {
    return base_price;
}
