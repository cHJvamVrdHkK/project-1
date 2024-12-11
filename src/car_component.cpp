#include "car_component.hpp"
#include "car_engine.hpp"

car_component *car_component::create_from_csv(
        std::vector<std::string> const &fields) {
    car_component *result = nullptr;

    if (auto type = fields[0]; type == "Engine")  {
        result = new car_engine();
        dynamic_cast<car_engine *>(result)->from_csv(fields);
    } else if (type == "Color") {
        //result = std::make_unique<car_engine>();
        //std::dynamic_cast<car_engine>(result)->fromCSV(csvRow);
    } 

    return result;
}
