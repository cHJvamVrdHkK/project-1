#include "car_model.hpp"

#include <string>
#include <sstream>

std::string car_model::get_details() const {
    return desc;
}

float car_model::get_price() const {
    return base_price;
}

