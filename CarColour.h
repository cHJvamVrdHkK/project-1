#ifndef CAR_COLOUR_H
#define CAR_COLOUR_H

enum class CarChosedColour : U8  {
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
    U8 const *_name;
    CarChosedColour _colour;
};

#endif