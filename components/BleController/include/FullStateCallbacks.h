#pragma once

#include <stdio.h>
#include "NimBLEDevice.h"
#include "BleInformationTable.h"

class FullStateCallbacks: public NimBLECharacteristicCallbacks {
    BleInformationTable* table;

public:
    FullStateCallbacks ( BleInformationTable* table ) {
        this->table = table;
    }

    void onRead(NimBLECharacteristic* pCharacteristic) {
        pCharacteristic->setValue( table->getFullStateString() );
        printf("\nFullState read\n");
    };

    void onWrite(NimBLECharacteristic* pCharacteristic) {
        printf("%s : onWrite(), value: %s\n", 
                            pCharacteristic->getUUID().toString().c_str(),
                            pCharacteristic->getValue().c_str());
    };

    void onNotify(NimBLECharacteristic* pCharacteristic) {
        pCharacteristic->setValue( table->getFullStateString() );
        printf("\nSending notification to clients\n");
    };

    void onStatus(NimBLECharacteristic* pCharacteristic, Status status, int code) {
        printf("Notification/Indication status code: %d , return code: %d, %s\n",
                            status,
                            code,
                            NimBLEUtils::returnCodeToString(code));
    };
};