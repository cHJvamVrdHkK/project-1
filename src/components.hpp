#ifndef CAR_COMPONENTS_HPP
#define CAR_COMPONENTS_HPP

#include "car_component.hpp"

#include <vector>

class components {
public:
    class engine;
    class color;
    class wheels;
    class model;
};

class components::engine : public car_component {
public:
    enum class engine_kind { Petrol, Diesel, Electric, Hybrid, Invalid };
    enum class gear_box_kind { Manual, Automatic, Invalid };

    static std::string engine_kind_to_string(engine_kind kind);
    static engine_kind engine_kind_from_string(std::string const &str);

    static std::string gear_box_kind_to_string(gear_box_kind kind);
    static gear_box_kind gear_box_kind_from_string(std::string const &str);

    explicit engine(std::string name, float price, engine_kind kind, gear_box_kind gear_kind) 
        : car_component(name, price), kind(kind), gear_kind(gear_kind) {}

    std::string get_details() const;

private:
    engine_kind kind;
    gear_box_kind gear_kind;
};

class components::color : public car_component {
public:
    explicit color(std::string name, float price)
        : car_component(name, price) {}

    std::string get_details() const override;
};

class components::wheels : public car_component {
public:
    explicit wheels(std::string name, float price, float radius)
        : car_component(name, price), radius(radius) {}

    std::string get_details() const override;

private:
    float radius;
};

class components::model : public car_component {
public:
    explicit model(std::string name, float price, std::string desc)
        : car_component(name, price), desc(desc) {}

    std::string get_details() const override;

    void add_component(car_component *component) {
        components.push_back(component);
    }

    template<typename T>
        std::vector<T *> const get_components() const {
            std::vector<T *> result;
            for(auto *component : components) {
                if(T *c = dynamic_cast<T *>(component)) {
                    result.push_back(c);
                }
            }

            return result;
        }

private:
    std::vector<car_component *> components;
    std::string desc;
};

#endif //CAR_COMPONENTS_HPP
