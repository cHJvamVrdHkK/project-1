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
#if 0
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
#endif

    // TODO: Think about how all this loading resources stuff could be abstracted away
    {

        // Load enignes from file
        std::ifstream ifs("../resources/engines.csv");

        std::stringstream ss;
        std::string row;

        std::getline(ifs, row);
        for (;std::getline(ifs, row);) {
            ss.str(row);

            std::string id; std::getline(ss, id, ';');
            std::string name; std::getline(ss, name, ';');
            program::engines.push_back(std::make_shared<car_engine>(std::stoi(id), name));
        }

        ifs.close();

        // Load models from file
        ifs.open("../resources/models.csv");

        std::getline(ifs, row);
        for (;std::getline(ifs, row);) {
            ss.str(row);

            std::string id; std::getline(ss, id, ';');
            std::string name; std::getline(ss, name, ';');
            program::models.push_back(std::make_shared<car_model>(std::stoi(id), name));
        }

        ifs.close();

        ifs.open("../resources/features.csv");

        std::getline(ifs, row);
        for (;std::getline(ifs, row);) {
            ss.str(row);

            std::string model_id; std::getline(ss, model_id, ';');
            std::string feature; std::getline(ss, feature, ';');
            std::string feature_id; std::getline(ss, feature_id, ';');

            // First find model in the global list
            std::shared_ptr<car_model> model;
            for(auto m : program::models)
                if(m->get_id() == std::stoi(model_id)) {
                    model = m;
                    break;
                }

            // Then check what feature are we dealing with
            if(feature == "Engine") {
                // Get a reference to engines for car model
                auto &engines = model->get_engines();
                // Search for the engine and append to the list then exit the loop
                for(auto e : program::engines)
                    if(e->get_id() == std::stoi(feature_id)) {
                        engines.push_back(e);
                        break;
                    }
            }
        }

        ifs.close();
    }

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
