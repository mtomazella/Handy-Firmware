#pragma once

#include <stdio.h>
#include "NimBLEDevice.h"
#include "BleEventTrigger.h"

class SetterStateCallbacks: public NimBLECharacteristicCallbacks {
    BleEventTrigger* eTrigger;

public:
    SetterStateCallbacks ( BleEventTrigger* eTrigger ) {
        this->eTrigger = eTrigger;
    }

    void onRead(NimBLECharacteristic* pCharacteristic) {
        printf("\nToggle State\n");
        eTrigger->toggleState();
    };

    void onWrite(NimBLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue().c_str();
        bool state = ( value == "1" ) ? true : false;
        printf("\nState set to %d via BLE", state);
        eTrigger->setState( state );
    };

    void onNotify(NimBLECharacteristic* pCharacteristic) { };
    void onStatus(NimBLECharacteristic* pCharacteristic, Status status, int code) { };
};