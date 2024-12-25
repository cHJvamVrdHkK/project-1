#include "car_drive.hpp"

#include <vector>
#include <string>
#include <memory>

std::shared_ptr<car_drive> read_colour(std::vector<std::string> const &row) {
    auto result = std::make_shared<car_drive>();
    result->name = row[]; //put suitable row here

    return result;
}

std::string car_drive::to_csv() const {
    return "";
}

void car_drive::from_csv(std::vector<std::string> const &fields) {
    this->name = fields[]; //put suitable field here
}