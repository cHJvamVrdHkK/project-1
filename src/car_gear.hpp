#ifndef CAR_GEAR_HPP
#define CAR_GEAR_HPP
#include "car_component.hpp"

#include <string>
#include <cstdint>
#include <vector>
#include <memory>


enum class CarChosedGear : uint8_t  {
    automatic,
    manual,
    //Gears
};

struct car_gear : public car_component {
    std::string name;

    car_gear() = default;

    car_gear(uint64_t id, std::string name)
        : name(name) {}

    std::string to_csv() const override;

    void from_csv(std::vector<std::string> const &fields) override;
};

#endif