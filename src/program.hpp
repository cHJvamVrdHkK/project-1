#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>

class car_model;
class car_config;

class program {
public:
    static int main();

    static std::vector<car_model *> car_models;
    static std::vector<car_config *> car_configs;
};

#endif //PROGRAM_HPP
