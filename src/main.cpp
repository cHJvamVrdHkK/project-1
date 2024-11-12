#include "car_config.hpp"
#include "car_model.hpp"
#include "car_engine.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <memory>

int main(int argc, char argv[]) {
    std::vector<std::shared_ptr<car_engine>> engines {
        std::make_shared<car_engine>("1.0L 3-cylinder Petrol", car_engine_kind::Petrol, 72.f, 93.f, 1'200.f),
        std::make_shared<car_engine>("1.5L Hybrid Petrol", car_engine_kind::Hybrid, 120.f, 135.f, 1'700.f),
    };

    car_model model("Toyota Yaris", engines, 20'000.f);
    car_config config;

    std::cout << "Wybierz model:\n";
    {
        for(auto engine : model.get_engines())
            std::cout << engine->get_name() << '\n';
        int n; std::cin >> n;
    }

    return 0;
}
