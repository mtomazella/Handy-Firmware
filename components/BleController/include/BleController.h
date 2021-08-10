#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include "NimBLEDevice.h"
#include "BleEventTrigger.h"
#include "global_variables.h"
#include "BleInformationTable.h"
    /* Callbacks */
#include "FullStateCallbacks.h"
#include "SetterModesCallbacks.h"
#include "SetterStateCallbacks.h"

class BleController {
    BleInformationTable* table;
    BleEventTrigger*     eTrigger;

    BLEServer*       server;
    BLEService*      serviceFullState;
    BLEService*      serviceSetters;
    BLEAdvertising*  advertising;

    BLECharacteristic* charFullState;
    BLECharacteristic* setterModes;
    BLECharacteristic* setterState;

public:
    BleController ( ) { };
    BleController ( std::string deviceName, BleInformationTable* table, BleEventTrigger* bleEventTrigger ) {
        BLEDevice::init( deviceName );

        this->table    = table;
        this->eTrigger = bleEventTrigger;

        server           = BLEDevice::createServer( );
        
        server->advertiseOnDisconnect( true );

        serviceFullState = server          ->createService       ( UUID_SERVICE_FULLSTATE );
        charFullState    = serviceFullState->createCharacteristic( UUID_CHARACT_FULLSTATE );
        charFullState->setCallbacks( new FullStateCallbacks( table ) );

        serviceSetters   = server        ->createService       ( UUID_SERVICE_SETTERS );
        setterModes      = serviceSetters->createCharacteristic( UUID_SETTER_MODES );
        setterState      = serviceSetters->createCharacteristic( UUID_SETTER_STATE );
        setterModes->setCallbacks( new SetterModesCallbacks( eTrigger ) );
        setterState->setCallbacks( new SetterStateCallbacks( eTrigger ) );

        serviceFullState->start( );
        serviceSetters  ->start( );

        advertising = BLEDevice::getAdvertising( );
        advertising->addServiceUUID( UUID_SERVICE_FULLSTATE );
        advertising->addServiceUUID( UUID_SERVICE_SETTERS   );
        
        advertising->start( );
    }
};