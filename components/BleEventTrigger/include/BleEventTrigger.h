#pragma once

#include <string>
#include "HardwareController.h"
#include "StorageController.h"
#include "Hand.h"

class BleEventTrigger {
    HardwareController* hController;
    Hand*               hand;
    StorageController*  storage;

public:
    BleEventTrigger ( void ) { }
    BleEventTrigger ( Hand* hand, HardwareController* hController, StorageController* storage ) {
        this->hController   = hController;
        this->hand          = hand;
        this->storage       = storage;
    }

    void toggleState ( void );
    void setState    ( bool state );
    void toggleMode  ( void );
    void setModes    ( std::string );
};
