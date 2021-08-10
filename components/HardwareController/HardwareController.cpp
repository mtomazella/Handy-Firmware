#include <stdio.h>
#include <iostream>
#include "HardwareController.h"
#include "Gpio.h"

void HardwareController::init ( void ) {
    for ( int i = 0; i < FINGER_COUNT; i++ ) {
        _fingers[i].init();
        _fingers[i].set( 0 );
    }
    _state_btn.init( );
    _mode_btn.init ( );

    setHandState( false );
    actuateFingers();

    modeBtn_setup ( );
    stateBtn_setup( );
    
    _ble_table->setState    ( _hand->get_state()            );
    _ble_table->setModeIndex( _hand->get_currentModeIndex() );
    _ble_table->setModeName ( _hand->get_currentModeName()  );
}

void HardwareController::listen ( void ) {   
    if ( _wait_flag ) return;

    modeBtn_loop ( _mode_btn.get ( ) );
    stateBtn_loop( _state_btn.get( ) );

    if ( _state_processing_flag || _state_changed_flag ) actuateFingers();
}

void HardwareController::setHandState ( void ) {
    bool state = _hand->get_state() | _ble_state;
    if ( _hand->get_state() != state ) { 
        _state_changed_flag = true;
        for ( int i = 0; i < FINGER_COUNT; i++ ) initialAngles[i] = _fingers[i].get();
        _hand->set_state( state );
        _ble_table->setState( state );
        time = 0;
    }
}
void HardwareController::setHandState ( bool state ) {
    state = state | _ble_state;
    if ( _hand->get_state() != state ) { 
        _state_changed_flag = true;
        for ( int i = 0; i < FINGER_COUNT; i++ ) initialAngles[i] = _fingers[i].get();
        _hand->set_state( state );
        _ble_table->setState( state );
        time = 0;
    }
}

void HardwareController::switchHandMode ( void ) {
    _hand->switchMode();
    setHandState( _hand->get_state() );
    _ble_table->setModeIndex( _hand->get_currentModeIndex() );
    _ble_table->setModeName ( _hand->get_currentModeName()  );
}

void HardwareController::actuateFingers ( void ) {
    _state_changed_flag = false;

    Mode* mode  = _hand->get_currentMode();
    bool  state = _hand->get_state();
    
    if ( mode == NULL ) return;

    _state_processing_flag = true;
    if ( time > mode->get_duration(state) ) {
        _state_processing_flag = false;
        if ( !_state_changed_flag ) time = 0;
        return;
    }
    
    ModeOption fingerState = mode->get_stateValues( state );
    for ( int i = 0; i < FINGER_COUNT; i++ ) {
        int angle    = fingerState[i][0];
        int start    = fingerState[i][1];
        int duration = fingerState[i][2];
        printf("\n\n%d , %d , %d , %d", time, angle, start, duration);
        if ( time >= start && time <= start+duration ) {
            if ( duration == 0 ) _fingers[i].set( angle );
            else _fingers[i].set( initialAngles[i] + ( angle - initialAngles[i] )/duration * ( time - start ) );
        } else if ( time > start + duration )
            _fingers[i].set( angle );
    }

    this->time += 1;
}


    /* Handlers */

void HardwareController::modeBtn_setup  ( void ) {

}
void HardwareController::stateBtn_setup  ( void ) {
    state_led = Gpio::GpioOutput( GPIO_NUM_21 );
    state_led.init();
}

void HardwareController::modeBtn_loop  ( bool state ) {
    if ( state ) {

        if ( !_mode_pressed_flag ) {
            _mode_pressed_flag = true;
            printf( "\nMode\n" );
            switchHandMode();
        }
        else return;

    } else {

        _mode_pressed_flag = false;

    }
}
void HardwareController::stateBtn_loop ( bool state ) {
    if ( state ) {

        // printf( "\nState\n" );
        state_led.set( true );
        setHandState( true );

    } else {

        setHandState( false );
        state_led.set( false );

    }
}
