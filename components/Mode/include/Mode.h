#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include "global_variables.h"
#include "types.h"

using namespace std;

class Mode {
    public:
        char*      name              = (char*) malloc( sizeof( char ) * 30 );
        ModeOption deactivatedValues = {{ {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0} }};
        ModeOption activatedValues   = {{ {180,0,0},{180,0,0},{180,0,0},{180,0,0},{180,0,0} }};

        mutable int durationOpen  = 0;
        mutable int durationClose = 0;

        Mode ( char* name, ModeOption open, ModeOption closed );
        // Mode ( char* name, int* open, int* closed );
        Mode ( char* name );

        void defineDuration ( );
        int  get_duration ( bool state );

        void print_values ( bool state );
        string get_stringRepresentation ( );
        ModeOption get_stateValues ( bool state );
        void set_name ( char* mode_name );
        void set_values ( bool state, ModeOption values );
        // void set_values ( bool state, int* values );
};