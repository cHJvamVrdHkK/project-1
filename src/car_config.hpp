#ifndef CAR_CONFIG_HPP
#define CAR_CONFIG_HPP

#include <memory>

struct car_model;
struct car_engine;

struct car_config {
    car_model *model;
    car_engine *engine;

};

#endif //CAR_CONFIG_HPP
