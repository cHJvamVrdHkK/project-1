#ifndef CAR_CONFIG_HPP
#define CAR_CONFIG_HPP

#include <memory>

class car_engine;

class car_config {
    std::shared_ptr<car_engine> engine;

public:
    void set_engine(std::shared_ptr<car_engine> engine) {
        this->engine = std::move(engine);
    }
};

#endif //CAR_CONFIG_HPP
