#pragma once

#include <driver/gpio.h>
#include "servoControl.h"

namespace Gpio {

    class GpioBase {
    protected:
        mutable gpio_num_t _pin;
        mutable bool       _inverted    = false;
        mutable esp_err_t  _fatal_error = ESP_OK;

    public:
        GpioBase ( ) { _fatal_error = ESP_ERR_INVALID_STATE; }
        GpioBase ( const gpio_num_t pin, const bool inverted = false ) :
            _pin{pin},
            _inverted{inverted}
        {
            gpio_pad_select_gpio( pin );
            //printf( "Pin %d set as Gpio\n", pin );    
        }

        void setFatalError ( const esp_err_t status ) const;
        bool isBroken ( void ) const;
    };

    class GpioOutput : public GpioBase {
        mutable bool _state = false;
        mutable servoControl _pwm;
        mutable bool _isPwm = false;
        mutable int _angle = 0;
    public:
        GpioOutput ( ) {
            _fatal_error = ESP_ERR_INVALID_STATE;
        }
        GpioOutput ( gpio_num_t pin, const bool inverted = false, const bool isPwm = false ) :
            GpioBase{ pin, inverted }
        {
            _isPwm = isPwm;
        }

        int       get ( void ) const;
        esp_err_t set ( const int state ) const;

        esp_err_t init ( void ) const;
    };


    class GpioInput : public GpioBase {
    public:
        GpioInput ( ) {
            _fatal_error = ESP_ERR_INVALID_STATE;
        }
        GpioInput ( const gpio_num_t pin, const bool inverted = false ) :
            GpioBase{ pin, inverted }
        {

        }

        bool      get ( void ) const;
        esp_err_t set ( bool state ) const;

        esp_err_t init ( void ) const;
    };

}