#include "program.hpp"
#include "car_config.hpp"
#include "car_model.hpp"
#include "car_engine.hpp"

#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>

int main(int argc, char **argv) {
    program::engines.push_back(std::make_shared<car_engine>("Engine 1"));
    program::engines.push_back(std::make_shared<car_engine>("Engine 2"));
    program::engines.push_back(std::make_shared<car_engine>("Engine 3"));
    program::engines.push_back(std::make_shared<car_engine>("Engine 4"));

    std::vector<std::shared_ptr<car_engine>> engines;
    for(int i = 0; i < program::engines.size(); ++i)
        if(i % 2 == 0)
            engines.push_back(program::engines[i]);
    program::models.push_back(std::make_shared<car_model>("Model 1", engines));

    engines.clear();
    for(int i = 0; i < program::engines.size(); ++i)
        if(i % 2 != 0)
            engines.push_back(program::engines[i]);
    program::models.push_back(std::make_shared<car_model>("Model 2", engines));

    // Create configuration
    {
        car_config new_config;

        std::shared_ptr<car_model> selected_model; 

        std::cout << "Wybierz model\n";
        {
            int i = 0;
            for(auto &model : program::models)
                std::cout << ++i << ". " << model->get_name() << '\n';

            std::cout << ">> " << std::flush;
            int n; std::cin >> n;

            assert(n < program::models.size());

            new_config.set_model(selected_model = program::models[n]);
        }


        std::cout << "Wybierz silnik\n";
        {
            auto &engines = selected_model->get_engines();

            int i = 0;
            for(auto &model : engines)
                std::cout << ++i << ". " << model->get_name() << '\n';

            std::cout << ">> " << std::flush;
            int n; std::cin >> n;

            assert(n < engines.size());

            new_config.set_engine(engines[n]);
        }

        std::cout << new_config.get_model()->get_name() << '\n';
        std::cout << new_config.get_engine()->get_name() << '\n';
    }

    return 0;
}
