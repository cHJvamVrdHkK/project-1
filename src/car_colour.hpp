#ifndef CAR_COLOUR_H
#define CAR_COLOUR_H
#include "car_component.hpp"

#include <string>
#include <cstdint>
#include <vector>
#include <memory>


enum class CarChosedColour : uint8_t  {
    white,
    black,
    red,
    green,
    silver,
    blue,
    //Palette of colours available  
};

struct car_colour : public car_component {
    std::string name;
    //Colours

    car_colour() = default;

    car_colour(uint64_t id, std::string name)
        : name(name) {}

    std::string to_csv() const override;

    void from_csv(std::vector<std::string> const &fields) override;
};

#endif