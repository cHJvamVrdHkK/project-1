#ifndef CAR_ENGINE_HPP
#define CAR_ENGINE_HPP

#include <string>
#include <cstdint>

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

class car_engine {
    std::string name;
    car_engine_kind kind;
    float power, torque;
    float price;

public:
    car_engine(const std::string& name, car_engine_kind kind, float power, float torque, float price) 
        : name(name), kind(kind), power(power), torque(torque), price(price) {}

    const std::string& get_name() const;
};

#endif //CAR_ENGINE_HPP
