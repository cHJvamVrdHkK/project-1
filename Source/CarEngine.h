#ifndef CAR_ENGINE_H
#define CAR_ENGINE_H

enum class CarEngineKind : U8 {
    /** Combustion engine using petrol as fuel */
    Petrol,
    /** Combustion engine using diesel as fuel */
    Diesel,
    /** Electric motor instead of combustion engine */
    Electric,
    /** Combustion engine and electric motor */
    Hybrid,
};

class CarEngine {
private:
    U8 const *_name;
    CarEngineKind _kind;
    F32 _power, _torque;
    F32 _price;
};

#endif //CAR_ENGINE_H
