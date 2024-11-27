#include "program.hpp"

std::vector<std::shared_ptr<car_engine>> program::engines;
std::vector<std::shared_ptr<car_model>> program::models;

void program::init() {

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
