#include "car_engine.hpp"
#if 0
#include "..."

void to_csv(csv_context &csv, car_engine const &object) {
    ...
}

void from_csv(csv_context &csv, car_engine &object) {
    ...
    // read row
    auto row = csv.next_row();
    auto row.get<...>();
}

#endif
