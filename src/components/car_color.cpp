#include "car_color.hpp"

#include <sstream>

std::string car_color::get_details() const {
	std::stringstream ss;
	ss << "color: " << name <<  "\n";

	return ss.str();
}

unsigned int car_color::calculate_price() const {
	return base_price;
}
