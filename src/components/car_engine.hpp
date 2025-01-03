#ifndef CAR_ENGINE_HPP
#define CAR_ENGINE_HPP

#include "car_component.hpp"

#include <cstdint>

enum class engine_kind : uint8_t {
    Petrol, Diesel, Electric, Hybrid, Invalid
};

std::string engine_kind_to_string(engine_kind kind);
engine_kind engine_kind_from_string(std::string const &str);

enum class gear_box_kind : uint8_t {
    Manual, Automatic, Invalid
};

std::string gear_box_kind_to_string(gear_box_kind kind);
gear_box_kind gear_box_kind_from_string(std::string const &str);

class car_engine : public car_component {
public:
    explicit car_engine(std::string name, float price, engine_kind kind, gear_box_kind gear_kind) 
        : car_component(name, price), kind(kind), gear_kind(gear_kind) {}

    std::string get_details() const;
    float get_price() const;

private:
    engine_kind kind;
    gear_box_kind gear_kind;
};

#endif //CAR_ENGINE_HPP
