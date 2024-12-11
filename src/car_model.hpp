#ifndef CAR_MODEL_HPP
#define CAR_MODEL_HPP

#include "car_engine.hpp"

#include <vector>
#include <string>
#include <memory>

struct car_component;
struct car_engine;

struct car_model {
    std::string name;
    std::vector<car_component *> components;

    car_model() = default;

    car_model(uint64_t id, std::string name)
        : name(std::move(name)) {}

    std::vector<car_engine *> get_engines() {
        std::vector<car_engine *> result;
        for(auto *component : components) {
            if(auto *engine = dynamic_cast<car_engine *>(component)) {
                result.push_back(engine);
            }
        }

        return result;
    }

};

#endif //CAR_MODEL_HPP
