#include <string>
#include <sstream>
#include "BleInformationTable.h"

std::string BleInformationTable::getFullStateString ( void ) {
    std::stringstream state;

    state << 
     "battery_level:" << getBatteryLevel() << 
    ",state:"         << getState()        << 
    ",mode_index:"    << getModeIndex()    << 
    ",mode_name:"     << getModeName()      ;

    return state.str();
}