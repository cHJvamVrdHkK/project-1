#ifndef CAR_ENGINE_HPP
#define CAR_ENGINE_HPP

#include "car_component.hpp"

#include <string>
#include <cstdint>
#include <vector>
#include <memory>

enum class car_engine_kind : uint8_t {
    // Combustion engine using petrol as fuel
    Petrol,
    // Combustion engine using diesel as fuel
    Diesel,
    // Electric motor instead of combustion engine
    Electric,
    // Combustion engine and electric motor
    Hybrid,
};

struct car_engine : public car_component {
    std::string name;
    //car_engine_kind kind;
    //float power, torque;
    //float price;

    car_engine() = default;

    car_engine(uint64_t id, std::string name)
        : name(name) {}

    std::string to_csv() const override;

    void from_csv(std::vector<std::string> const &fields) override;
};

//std::shared_ptr<car_engine> read_engine(std::vector<std::string> const &row);

#endif //CAR_ENGINE_HPP
