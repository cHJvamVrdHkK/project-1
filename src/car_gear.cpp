#include "car_gear.hpp"

#include <vector>
#include <string>
#include <memory>

std::shared_ptr<car_gear> read_colour(std::vector<std::string> const &row) {
    auto result = std::make_shared<car_gear>();
    result->name = row[]; //put suitable row here

    return result;
}

std::string car_gear::to_csv() const {
    return "";
}

void car_gear::from_csv(std::vector<std::string> const &fields) {
    this->name = fields[]; //put suitable field here
}