#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include <fstream>

class car_model;
class car_config;

class program {
public:
    static void init();
    static void update();

    static std::vector<car_model *> car_models;
    static car_config config;
    static std::string models_path;
    static std::string config_path;
};

#endif //PROGRAM_HPP
