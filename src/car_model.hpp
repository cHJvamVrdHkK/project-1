#ifndef CAR_MODEL_HPP
#define CAR_MODEL_HPP

#include <vector>
#include <string>
#include <memory>

class car_engine;

class car_model {
    std::string name;
    std::vector<std::shared_ptr<car_engine>> engines;
    int base_price;

public:
    car_model(std::string name, std::vector<std::shared_ptr<car_engine>> engines, 
              int base_price = 0) 
        : name(std::move(name)), engines(std::move(engines)), base_price(base_price) {}

    const std::vector<std::shared_ptr<car_engine>>& get_engines() const {
        return engines;
    }
};

#endif //CAR_MODEL_HPP
