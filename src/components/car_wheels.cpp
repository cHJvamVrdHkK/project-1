#include "car_wheels.hpp"

#include <sstream>

std::string car_wheels::get_details() const {
    std::stringstream ss;
    ss << "wheels: " << name <<  "\n";

    return ss.str();
}

unsigned int car_wheels::calculate_price() const {
    return base_price;
}
