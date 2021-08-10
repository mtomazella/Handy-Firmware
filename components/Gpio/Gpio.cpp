#include <stdio.h>
#include "Gpio.h"
#include "global_variables.h"

namespace Gpio {

    void GpioBase::setFatalError ( const esp_err_t status ) const {
        _fatal_error |= status;
    }
    bool GpioBase::isBroken ( void ) const {
        return _fatal_error != ESP_OK ? true : false;
    }

    esp_err_t GpioOutput::init ( void ) const {
        const esp_err_t status = gpio_set_direction( _pin, GPIO_MODE_OUTPUT );
        if ( _isPwm ) {
            const bool firstTimerFull = CURRENT_LEDC_CHANNEL > 7;
            _pwm.attach( _pin, 400, 2600, (ledc_channel_t) (firstTimerFull?CURRENT_LEDC_CHANNEL-8:CURRENT_LEDC_CHANNEL), firstTimerFull?LEDC_TIMER_1:LEDC_TIMER_0 );
            // printf("\n\n%d\t%d\t%d\n\n",firstTimerFull,(ledc_channel_t)(firstTimerFull?CURRENT_LEDC_CHANNEL-8:CURRENT_LEDC_CHANNEL),firstTimerFull?LEDC_TIMER_1:LEDC_TIMER_0 );
            CURRENT_LEDC_CHANNEL++;
        }
        this->set( 0 );
        setFatalError( status );
        return status;
    }
    esp_err_t GpioOutput::set ( const int state ) const {
        if ( isBroken() ) return _fatal_error;

        if ( _isPwm ) {
            _angle = state;
            _pwm.write( _angle );
            return ESP_OK;
        }

        _state = (bool)state;
        const bool t_state = _inverted ? !state : state;
        const esp_err_t status = gpio_set_level( _pin, (int) t_state );
        
        setFatalError( status );
        if ( status != 0 ) printf( "Error" );
        return status;
    }
    int GpioOutput::get ( void ) const {
        if ( _isPwm ) return _angle;
        return _inverted ? !_state : _state;
    }



    esp_err_t GpioInput::init ( void ) const {
        const esp_err_t status = gpio_set_direction( _pin, GPIO_MODE_INPUT );
        //printf( "Pin %d set as Input", _pin );
        setFatalError( status );
        return status;
    }
    bool GpioInput::get ( void ) const {
        const int state = gpio_get_level( _pin );
        return state <= 0 ? false : true;
    }
    esp_err_t GpioInput::set ( bool state ) const { 
        return ESP_ERR_NOT_SUPPORTED;
    }

}