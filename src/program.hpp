#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include <memory>

class car_engine;
class car_model;

struct program {
    static std::vector<car_model *> models;

    static void init();
};

#endif //PROGRAM_HPP
