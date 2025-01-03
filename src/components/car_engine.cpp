#include "car_engine.hpp"

#include <sstream>

std::string engine_kind_to_string(engine_kind kind) {
    switch(kind) {
        break;case engine_kind::Petrol: 	return "Petrol";
        break;case engine_kind::Diesel: 	return "Diesel";
        break;case engine_kind::Electric: 	return "Electric";
        break;case engine_kind::Hybrid: 	return "Hybrid";
    }
    return "Invalid";
}

engine_kind engine_kind_from_string(std::string const &str) {
    if(str == "Petrol") {
        return engine_kind::Petrol;
    } else if(str == "Diesel") {
        return engine_kind::Diesel;
    } else if(str == "Electric") {
        return engine_kind::Electric;
    } else if(str == "Hybrid") {
        return engine_kind::Hybrid;
    }

    return engine_kind::Invalid;
}

std::string gear_box_kind_to_string(gear_box_kind kind) {
    switch(kind) {
        break;case gear_box_kind::Manual: 		return "Manual";
        break;case gear_box_kind::Automatic: 	return "Automatic";
    }
    return "Invalid";
}

gear_box_kind gear_box_kind_from_string(std::string const &str) {
    if(str == "Manual") {
        return gear_box_kind::Manual;
    } else if(str == "Automatic") {
        return gear_box_kind::Automatic;
    }

    return gear_box_kind::Invalid;
}

std::string car_engine::get_details() const {
    std::stringstream ss;
    ss << "engine: " << name <<  "\n";
    ss << '\t' << "kind: " << engine_kind_to_string(kind) <<  "\n";
    ss << '\t' << "gear box: " << gear_box_kind_to_string(gear_kind) <<  "\n";

    return ss.str();
}

unsigned int car_engine::calculate_price() const {
    return base_price;
}

