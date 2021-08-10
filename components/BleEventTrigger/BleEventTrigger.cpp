#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "global_variables.h"
#include "BleEventTrigger.h"
#include "Mode.h"

void BleEventTrigger::toggleState ( void ) {
    hController->toggleBleState();
}

void BleEventTrigger::setState ( bool state ) {
    hController->setBleState( state );
}

void BleEventTrigger::toggleMode ( void ) {
    hController->bleToggleMode();
}

// name1;0,0,0,0,0;1,1,1,1,1|name2;0,0,0,0,0;1,1,1,1,1
void BleEventTrigger::setModes ( std::string modes ) {
    hand->initFromModesString( modes );
    storage->write( "modes", modes ); 
}