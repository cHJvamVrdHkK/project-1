#ifndef EDITOR_H
#define EDITOR_H

#include "Base/Types/BaseTypes.h"

#include "CarEngine.h"
#include "CarModel.h"
#include "CarColour.h"
#include "CarWheels.h"
#include "CarConfig.h"


struct Editor {
    static CarConfig *savedConfigs;

    static S32 Main();
};

S32 Editor::Main() {
    return 0;
}

#endif //EDITOR_H
