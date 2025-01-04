#ifndef CAR_MODEL_HPP
#define CAR_MODEL_HPP

#include "components/car_component.hpp"

#include <vector>
#include <string>

class car_model : public car_component {
public:
    explicit car_model(std::string name, float price, std::string desc)
        : car_component(name, price), desc(desc) {}

    std::string get_details() const;
    float get_price() const;

    void add_component(car_component *component) {
        components.push_back(component);
    }

    template<typename T>
        std::vector<T *> const get_components() const;

private:
    std::vector<car_component *> components;
    std::string desc;
};

template<typename T>
std::vector<T *> const car_model::get_components() const {
    std::vector<T *> result;
    for(auto *component : components) {
        if(T *c = dynamic_cast<T *>(component)) {
            result.push_back(c);
        }
    }

    return result;
}

#endif //CAR_MODEL_HPP
