#include "car_colour.hpp"

#include <vector>
#include <string>
#include <memory>

std::shared_ptr<car_colour> read_colour(std::vector<std::string> const &row) {
    auto result = std::make_shared<car_colour>();
    result->name = row[]; //put suitable row here

    return result;
}

std::string car_colour::to_csv() const {
    return "";
}

void car_colour::from_csv(std::vector<std::string> const &fields) {
    this->name = fields[]; //put suitable field here
}