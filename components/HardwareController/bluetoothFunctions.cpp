#include "HardwareController.h"

void HardwareController::toggleBleState ( ) {
    _ble_state = !_ble_state;
    setHandState();
}

void HardwareController::setBleState ( bool state ) {
    _ble_state = state;
    setHandState();
}

void HardwareController::bleToggleMode ( ) {
    switchHandMode( );
}