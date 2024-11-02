#ifndef CAR_MODEL_H
#define CAR_MODEL_H

class CarModel {
private:
    U8 const *_name;
    CarEngine *_availableEngines;
    U32 *_availableColors;
};

#endif //CAR_MODEL_H
