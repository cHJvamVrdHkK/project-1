#ifndef CAR_Wheels_H
#define CAR_Wheels_H

enum class CarWheelType : W8  {
    standard,
    sport,
    fullYear,
};

class CarColour {
public:
    W8 const *_name;
    CarWheelType _Wheeltype;
};

#endif