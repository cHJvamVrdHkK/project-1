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
#include <type_traits>

std::vector<std::vector<std::string>> read_csv(std::string const &path) {
    std::ifstream file(path);

    std::vector<std::vector<std::string>> result;
    for(std::string row; std::getline(file, row);) {
        std::stringstream ss(row); std::vector<std::string> tokens; 
        for(std::string token; std::getline(ss, token, ';');) {
            tokens.push_back(token);
        }
        result.push_back(std::move(tokens));
    }

    file.close();

    return result;
}

template<typename T>
class repository {
    static_assert(std::is_base_of<car_feature, T>::value, "Type must inherit from car_feature.");

    std::vector<std::shared_ptr<T>> entities;
    public:
    repository() {
    }

    void add(std::shared_ptr<T> entity) {
        entities.push_back(entity);
    }
};

int main(int argc, char **argv) {

    program::init();

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

        std::ofstream ofs("../resources/configs.csv", std::ios::app);
        if(ofs.is_open()) {
            ofs << new_config.get_model()->get_name() << ';';
            ofs << new_config.get_engine()->get_name() << ';';
            ofs << '\n';
        }
    }

    return 0;
}

// sala 201
