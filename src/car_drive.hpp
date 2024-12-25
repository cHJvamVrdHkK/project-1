#ifndef CAR_DRIVE_HPP
#define CAR_DRIVE_HPP
#include "car_component.hpp"

#include <string>
#include <cstdint>
#include <vector>
#include <memory>


enum class CarChosedDrive : uint8_t  {
	FWD,
	RWD,
	AWD,
    //Drives
};

struct car_drive : public car_component {
    std::string name;

    car_drive() = default;

    car_drive(uint64_t id, std::string name)
        : name(name) {}

    std::string to_csv() const override;

    void from_csv(std::vector<std::string> const &fields) override;
};

#endif