#pragma once

#include <array>
#include <string>
#include "global_variables.h"
#include "BleInformationTable.h"
#include "types.h"
#include "Hand.h"

class HardwareController {
    Hand*            _hand;
    FingerPins       _finger_pins;
    FingerArray      _fingers;
    BoolArraySizeFC  _isPwm;
    gpio_num_t       _state_btn_pin;
    Gpio::GpioInput  _state_btn;
    gpio_num_t       _mode_btn_pin;   
    Gpio::GpioInput  _mode_btn;  
        /* Flags */
    mutable bool _wait_flag             = false;
    mutable bool _mode_pressed_flag     = false;
    mutable bool _state_changed_flag    = false;
    mutable bool _state_processing_flag = false;
        /* Bluetooth */
    BleInformationTable* _ble_table        ;
    bool                 _ble_state = false;
        /* Actuation Execution */
    mutable int           time          = 0;
    mutable InitialAngles initialAngles    ;

public:
    HardwareController ( Hand* handPointer,
                        BleInformationTable* bleTable,
                        FingerPins fingerPins, 
                        BoolArraySizeFC isPwm,
                        gpio_num_t stateBtnPin, 
                        gpio_num_t modeBtnPin )
    { 
        _ble_table     = bleTable;
        _hand          = handPointer;
        _state_btn_pin = stateBtnPin;
        _mode_btn_pin  = modeBtnPin;
        _state_btn     = Gpio::GpioInput( stateBtnPin );
        _mode_btn      = Gpio::GpioInput( modeBtnPin  );
        _isPwm         = isPwm;

        for ( int i = 0; i < FINGER_COUNT; i++ ) {
            _finger_pins[i] = fingerPins[i];
            _fingers[i] = Gpio::GpioOutput( _finger_pins[i], false, _isPwm[i] );
        }
    }
    void init            ( void );
    void listen          ( void );
    void actuateFingers  ( void );
    void switchHandMode  ( void );
    void setHandState    ( void );
    void setHandState    ( bool state );
    void setFingerToAngle( int index, int angle );

        /* Handler Memory */
    Gpio::GpioOutput state_led;
    Gpio::GpioOutput mode_led[3];
    mutable int mode_number = 0;
        /* Handlers */    
    void modeBtn_setup  ( void );
    void modeBtn_loop   ( bool state );

    void stateBtn_setup ( void );
    void stateBtn_loop  ( bool state );
        /* Bluetooth */
    void toggleBleState ( void );
    void setBleState    ( bool state );
    void bleToggleMode  ( void );
};