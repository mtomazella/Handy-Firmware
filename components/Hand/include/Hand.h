#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "global_variables.h"
#include "Mode.h"
#include "StorageController.h"

using namespace std;

class Hand {
    public:
        Mode* modes[MODE_COUNT] = { NULL, NULL, NULL };
        bool  state             = false;
        Mode* currentMode       = modes[0];
        int   currentModeIndex  = 0;

        void initModes ( StorageController* storage );
        void initFromModesString ( std::string modes );

        bool get_state ( )            { return state;        }
        void set_state ( bool state ) { this->state = state; }
        
        Mode*       get_currentMode      ( ) { return currentMode;       }
        int         get_currentModeIndex ( ) { return currentModeIndex;  }
        std::string get_currentModeName  ( ) { return currentMode->name; }
        
        string get_currentModeStringRepresentation ( ) 
        { return currentMode -> get_stringRepresentation(); }
        
        void print_currentMode ( ) { printf( "%s", currentMode -> name ); }
        /*
            Retorna a posição onde o modo foi adicionado no array modos.
            Se o array atingiu seu tamanho máximo, retorna -1.
        */
        int  addMode    ( Mode* newMode );
        void clearModes ( void );
        void switchMode ( void );
};