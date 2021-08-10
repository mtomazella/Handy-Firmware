#ifndef TYPE_FILE_DECLARED
#define TYPE_FILE_DECLARED

#include <array>
#include <map>
#include <functional>
#include "global_variables.h"
#include "driver/gpio.h"
#include "Gpio.h"

using namespace std;

typedef array<bool,FINGER_COUNT>            BoolArraySizeFC            ;
typedef array<int,3>                        ModeOptionState            ;
typedef array<ModeOptionState,FINGER_COUNT> ModeOption                 ;
typedef array<gpio_num_t,FINGER_COUNT>      FingerPins                 ;
typedef Gpio::GpioOutput                    FingerArray [FINGER_COUNT] ;
typedef array<int,FINGER_COUNT>             InitialAngles              ;

using FunctionMap = map<string, function<void(void)>>;

#endif