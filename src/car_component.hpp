#ifndef CAR_COMPONENT_HPP
#define CAR_COMPONENT_HPP

#include <string>
#include <memory>
#include <vector>

struct car_component {
    virtual std::string to_csv() const = 0;
    virtual void from_csv(std::vector<std::string> const &fields) = 0;

    static car_component *create_from_csv(std::vector<std::string> const &fields);
};

#endif //CAR_COMPONENT_HPP
