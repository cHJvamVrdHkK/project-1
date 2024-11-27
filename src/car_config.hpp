#ifndef CAR_CONFIG_HPP
#define CAR_CONFIG_HPP

#include <memory>

class car_model;
class car_engine;

class car_config {
    std::shared_ptr<car_model> model;
    std::shared_ptr<car_engine> engine;

public:
    const std::shared_ptr<car_model> get_model() const {
        return this->model;
    }

    const std::shared_ptr<car_engine> get_engine() const {
        return this->engine;
    }

    void set_model(std::shared_ptr<car_model> model) {
        this->model = std::move(model);
    }

    void set_engine(std::shared_ptr<car_engine> engine) {
        this->engine = std::move(engine);
    }
};

#endif //CAR_CONFIG_HPP
