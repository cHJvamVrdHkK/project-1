#ifndef CAR_COLOUR_H
#define CAR_COLOUR_H

enum class CarChosedColour : C8  {
    white,
    black,
    red,
    green,
    silver,
    blue,
    //Palette of colours available  
};

class CarColour {
public:
    C8 const *_name;
    CarChosedColour _colour;
};

#endif