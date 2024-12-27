#ifndef CAR_MODEL_HPP
#define CAR_MODEL_HPP

#include <vector>
#include <string>

class car_component;

class car_model {
public:
    car_model(std::string name)
        : name(name) {}

	std::string const &get_name() const {
		return name;
	}

	void add_component(car_component *component) {
		components.push_back(component);
	}

	template<typename T>
    std::vector<T *> const get_components() const;

private:
    std::string name;
    std::vector<car_component *> components;
};

template<typename T>
std::vector<T *> const car_model::get_components() const {
	std::vector<T *> result;
	for(auto *component : components) {
		if(T *c = dynamic_cast<T *>(component)) {
			result.push_back(c);
		}
	}

	return result;
}

#endif //CAR_MODEL_HPP
