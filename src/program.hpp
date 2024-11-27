#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include <memory>

class car_engine;
class car_model;

struct program {
    static std::vector<std::shared_ptr<car_engine>> engines;
    static std::vector<std::shared_ptr<car_model>> models;

    static void init();
};

#endif //PROGRAM_HPP
