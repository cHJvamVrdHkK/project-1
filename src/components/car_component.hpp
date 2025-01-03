#ifndef CAR_COMPONENT_HPP
#define CAR_COMPONENT_HPP

#include <string>

class car_component {
public:
    car_component(std::string name, unsigned int base_price)
        : name(name), base_price(base_price) {}

    virtual std::string get_details() const = 0;
    virtual float get_price() const = 0;

    virtual std::string const &get_name() const {
        return name;
    }

protected:
    std::string name;
    float base_price;
};

#endif //CAR_COMPONENT_HPP
