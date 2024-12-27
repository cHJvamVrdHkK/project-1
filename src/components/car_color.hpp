#ifndef CAR_COLOR_HPP
#define CAR_COLOR_HPP

#include "car_component.hpp"

class car_color : public car_component {
public:
	car_color() = default;
	car_color(std::string name) 
		: car_component(name, 100) {}

	std::string get_details() const;
	unsigned int calculate_price() const;

private:
};

#endif //CAR_COLOR_HPP
