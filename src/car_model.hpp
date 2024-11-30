#ifndef CAR_MODEL_HPP
#define CAR_MODEL_HPP

#include "car_feature.hpp"

#include <vector>
#include <string>
#include <memory>

class car_engine;

class car_model : public car_feature {
    std::string name;
    std::vector<std::shared_ptr<car_engine>> engines;

public:
    car_model(uint64_t id, std::string name)
        : car_feature(id), name(std::move(name)) {}

    const std::string &get_name() const {
        return name;
    }

    std::vector<std::shared_ptr<car_engine>> &get_engines() {
        return engines;
    }
};

#endif //CAR_MODEL_HPP
