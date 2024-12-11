#include "car_engine.hpp"

#include <vector>
#include <string>
#include <memory>

std::shared_ptr<car_engine> read_engine(std::vector<std::string> const &row) {
    auto result = std::make_shared<car_engine>();
    result->name = row[1];

    return result;
}

std::string car_engine::to_csv() const {
    return "";
}

void car_engine::from_csv(std::vector<std::string> const &fields) {
    this->name = fields[1];
}
