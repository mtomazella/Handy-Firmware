#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "NimBLEDevice.h"
#include "BleEventTrigger.h"

class SetterModesCallbacks: public NimBLECharacteristicCallbacks {
    BleEventTrigger* eTrigger;
    std::string modeString = "";

public:
    SetterModesCallbacks ( BleEventTrigger* eTrigger ) {
        this->eTrigger = eTrigger;
    }

    void onRead(NimBLECharacteristic* pCharacteristic) {
        printf("\nToggle Mode\n");
        eTrigger->toggleMode();
    };

    void onWrite(NimBLECharacteristic* pCharacteristic) { 
        modeString.append( pCharacteristic->getValue() );
        if ( modeString[modeString.length()-1] == '#' ) {
            eTrigger->setModes( modeString.substr(0,modeString.length()-1).c_str() );
            modeString = "";
        }
    };

    void onNotify(NimBLECharacteristic* pCharacteristic) { };
    void onStatus(NimBLECharacteristic* pCharacteristic, Status status, int code) { };
};