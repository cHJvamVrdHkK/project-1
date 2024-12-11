#include "program.hpp"
#include "car_config.hpp"
#include "car_model.hpp"
#include "car_engine.hpp"

#include <memory>
#include <string>
#include <fstream>
#include <sstream>

std::vector<car_model *> program::models;

#if 0
void program::init() {
    // TODO: Think about how all this loading resources stuff could be abstracted away
    {
        // Load enignes from file
        for (auto row : read_csv("../resources/engines.csv"))
            program::engines.push_back(
                    std::make_shared<car_engine>(std::stoi(row[0]), row[1]));

        // Load models from file
        for (auto row : read_csv("../resources/models.csv"))
            program::models.push_back(
                    std::make_shared<car_model>(std::stoi(row[0]), row[1]));

        for (auto row : read_csv("../resources/features.csv")) {

            // First find model in the global list
            std::shared_ptr<car_model> model;
            for(auto m : program::models) {
                if(m->get_id() == std::stoi(row[0])) {
                    model = m;
                    break;
                }
            }

            // Then check what feature we are dealing with
            if(row[1] == "Engine") {
                // Get a reference to engines for car model
                auto &engines = model->get_engines();
                // Search for the engine and append to the list then exit the loop
                for(auto e : program::engines) {
                    if(e->get_id() == std::stoi(row[2])) {
                        engines.push_back(e);
                        break;
                    }
                }
            }
        }
    }

#if 0
    std::ifstream ifs("../engines.csv");

    std::stringstream ss;
    for (std::string row; std::getline(ifs, row);) {
        ss.str(row);

        std::string name; std::getline(ss, name, ';');
        engines.push_back(std::make_shared<car_engine>(name));
    }

    ifs.close();
#endif
}

#endif
