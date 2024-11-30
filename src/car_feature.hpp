#ifndef CAR_FEATURE_HPP
#define CAR_FEATURE_HPP

#include <cstdint>

class car_feature {
protected:
    uint64_t id;
public:
    car_feature(uint64_t id)
        : id(id) {}

    const uint64_t get_id() const {
        return id;
    }
};

#endif //CAR_FEATURE_HPP
