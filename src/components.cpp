#include "components.hpp"

#include <sstream>

std::string components::engine::engine_kind_to_string(engine_kind kind) {
    switch(kind) {
        break;case engine_kind::Petrol:     return "Petrol";
        break;case engine_kind::Diesel:     return "Diesel";
        break;case engine_kind::Electric:   return "Electric";
        break;case engine_kind::Hybrid:     return "Hybrid";
    }
    return "Invalid";
}

components::engine::engine_kind
components::engine::engine_kind_from_string(std::string const &str) {
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

std::string components::engine::gear_box_kind_to_string(gear_box_kind kind) {
    switch(kind) {
        break;case gear_box_kind::Manual:       return "Manual";
        break;case gear_box_kind::Automatic:    return "Automatic";
    }
    return "Invalid";
}

components::engine::gear_box_kind
components::engine::gear_box_kind_from_string(std::string const &str) {
    if(str == "Manual") {
        return gear_box_kind::Manual;
    } else if(str == "Automatic") {
        return gear_box_kind::Automatic;
    }

    return gear_box_kind::Invalid;
}

std::string components::engine::get_details() const {
    std::stringstream ss;
    ss << engine_kind_to_string(kind) <<  ", " << gear_box_kind_to_string(gear_kind);

    return ss.str();
}

std::string components::color::get_details() const {
    return "";
}

std::string components::wheels::get_details() const {
    std::stringstream ss;
    ss << radius << "-calowe";

    return ss.str();
}

std::string components::model::get_details() const {
    return desc;
}
