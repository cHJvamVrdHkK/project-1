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

#if 0
int main(int argc, char **argv) {

    program::init();

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

        std::ofstream ofs("../resources/configs.csv", std::ios::app);
        if(ofs.is_open()) {
            ofs << new_config.get_model()->get_name() << ';';
            ofs << new_config.get_engine()->get_name() << ';';
            ofs << '\n';
        }
    }

    return 0;
}
#endif

#include <filesystem>

std::vector<std::vector<std::string>> read_csv(std::string const &path) {
    std::ifstream file(path);

    std::vector<std::vector<std::string>> result;
    for(std::string row; std::getline(file, row);) {
        std::stringstream ss(row); std::vector<std::string> tokens; 
        for(std::string token; std::getline(ss, token, ',');) {
            tokens.push_back(token);
        }
        result.push_back(std::move(tokens));
    }

    file.close();

    return result;
}

int main() {
    std::string path = "../resources/models";

    for (auto const &entry : std::filesystem::directory_iterator(path)) {
        auto model_path = entry.path();

        auto *model = new car_model();
        model->name = model_path.stem().string();

        auto rows = read_csv(model_path.string());
        for(auto row : rows) {
            model->components.push_back(car_component::create_from_csv(row));
        }

        program::models.push_back(model);
    }

    for(auto *model : program::models) {
        std::cout << model->name << '\n';
        for(auto *component : model->components) {
            if(auto *engine = dynamic_cast<car_engine *>(component))
                std::cout << '\t' << engine->name << '\n';
        }
        std::cout << '\n';
    }

    // Create configuration
    {
        car_config new_config;

        car_model *selected_model; 

        std::cout << "Wybierz model\n";
        {
            int i = 0;
            for(auto *model : program::models)
                std::cout << ++i << ". " << model->name << '\n';

            std::cout << ">> " << std::flush;
            int n; std::cin >> n;

            assert(n < program::models.size());

            new_config.model = selected_model = program::models[n];
        }


        std::cout << "Wybierz silnik\n";
        {
            auto engines = selected_model->get_engines();
            for(int i = 0; i < engines.size(); ++i) {
                std::cout << i << ". " << engines[i]->name << '\n';
            }

            std::cout << ">> " << std::flush;
            int n; std::cin >> n;

            new_config.engine = engines[n];
        }

        std::cout << new_config.model->name << ' ' << new_config.engine->name << '\n';
    }

    return 0;
}
