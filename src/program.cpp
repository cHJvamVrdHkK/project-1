#include "program.hpp"

#include "car_model.hpp"
#include "car_config.hpp"

#include "components/car_engine.hpp"
#include "components/car_color.hpp"
#include "components/car_wheels.hpp"

#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>
#include <iomanip>

std::vector<car_model *> program::car_models;

static void init_models() {
	std::string path = "../resources/models";

	// NOTE: Parsing every model config file in resources directory. 
	// Name of the file is car's make. Config file consists of 
	// instructions that are parsed by the code path below. Instruction's 
	// opcode is car component's name.
	std::ifstream file(path);

	car_model *current_model = nullptr;
	std::string line;
	for(int line_number = 1; std::getline(file, line); ++line_number) {
		if(line.empty()) continue;

		std::istringstream stream(line);

		std::string command; 
		stream >> command;

		if(command == "model") {
			std::string name;
			stream >> std::quoted(name);

			program::car_models.push_back(
					current_model = new car_model(name));
		} else {
			// NOTE: Check if model command was used and current_model exists so that it can be configured.
			if(current_model) {
				std::string name;
				stream >> std::quoted(name);

				if(command == "engine") {
					std::string kind_, gear_kind_;
					stream >> kind_ >> gear_kind_;

					engine_kind kind = engine_kind_from_string(kind_);
					if(kind == engine_kind::Invalid) {
						std::cerr << "Error in line " << line_number << ": Engine kind '" << kind_ << "' is not supported.\n";
						continue;
					}

					gear_box_kind gear_kind = gear_box_kind_from_string(gear_kind_);
					if(gear_kind == gear_box_kind::Invalid) {
						std::cerr << "Error in line " << line_number << ": Gear box kind '" << gear_kind_ << "' is not supported.\n";
						continue;
					}

					current_model->add_component(new car_engine(name, kind, gear_kind));
				} else if(command == "color") {
					float r, g, b;
					stream >> r >> g >> b;

					current_model->add_component(new car_color(name));
				} else if(command == "wheels") {
					int radius; 
					stream >> radius;

					current_model->add_component(new car_wheels(name, radius));
				} else {
					std::cerr << "Error in line " << line_number << ": Command '" << command << "' doesn't exist.\n";
				}
			} else {
				std::cerr << "Error in line " << line_number << ": trying to add car's components to a model, but haven't started any model yet.\n";
			}
		} 
	}

	file.close();
}

void save_config(std::ofstream &file, car_config *config) {
	for(auto *component : config->components) {
		file << component->get_details();
	}
}

template<typename T>
T *select_component(car_model *selected_model) {
	auto components = selected_model->get_components<T>();
	for(size_t i = 0; i < components.size(); ++i) {
		std::cout << i+1 << ". " << components[i]->get_name() << '\n';
	}

	int n = 0;
	while(n <= 0 || n > components.size()) {
		std::cout << ">> " << std::flush;
		std::cin >> n;
	}

	return components[n-1];
}

int program::main() {
#if 0
 	char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        result[count] = '\0'; // Null-terminate the string
        std::cout << "Executable is located at: " << result << std::endl;
    } else {
        std::cerr << "Failed to determine executable path!" << std::endl;
    }
#endif

    init_models();

	std::cout << "Witaj w konfiguratorze pojazdów.\n";

	car_model *selected_model; 
	{
		std::cout << "Wybierz model\n";

		size_t count = program::car_models.size();
		for(size_t i = 0; i < count; ++i) {
			auto *model = program::car_models[i];
			std::cout << i << ". " << model->get_name() << '\n';
		}

		std::cout << ">> " << std::flush;
		int n; std::cin >> n;

		selected_model = program::car_models[n];
	}

    // Create configuration
    {
		car_config config;
		config.model = selected_model;

        std::cout << "Wybierz silnik\n";
		config.components[0] = select_component<car_engine>(config.model);

        std::cout << "Wybierz kolor\n";
		config.components[1] = select_component<car_color>(config.model);

        std::cout << "Wybierz kola\n";
		config.components[2] = select_component<car_wheels>(config.model);

		std::ofstream file("../resources/configs");

		save_config(file, &config);

		file.close();
	}

	return 0;
}
