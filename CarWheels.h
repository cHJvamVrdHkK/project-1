#ifndef CAR_Wheels_H
#define CAR_Wheels_H

enum class CarWheelType : U8  {
    standard,
    sport,
    fullYear,
};

class CarColour {
public:
    U8 const *_name;
    CarWheelType _Wheeltype;
};

#endif