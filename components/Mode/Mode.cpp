#include "Mode.h"

#include <array>
#include <string>
#include <sstream>
#include <algorithm>
#include "types.h"

using namespace std;

string modeOptionToString ( ModeOption array, string separator ) {
    ostringstream string;
    string << "[ ";
    for ( short int i = 0; i < array.size(); i++ ) {
        string << "[ ";
        for ( short int j = 0; j < array[i].size(); j++ )
            string << array[i][j] << ",";
        string << " ]";
        if ( i != array.size() - 1 ) string << separator;
    }
    string << " ]";
    return string.str();
}

Mode::Mode ( char* name, ModeOption open, ModeOption closed ) {
    set_name( name );
    set_values( false, open );
    set_values( true, closed );
}
// Mode::Mode ( char* name, int* open, int* closed ) {
//     set_name( name );
//     set_values( false, open );
//     set_values( true, closed );
// }
Mode::Mode ( char* name ) {
    set_name( name );
}

void Mode::defineDuration ( ) {
    int maxClose = 0;
    int maxOpen  = 0;

    ModeOption valuesClose = get_stateValues(true) ;
    ModeOption valuesOpen  = get_stateValues(false);

    for ( int i = 0; i < 3; i++ ) {
        int durationC = valuesClose[i][1] + valuesClose[i][2];
        int durationO = valuesOpen[i][1]  + valuesOpen[i][2] ;
        if ( durationC > maxClose ) maxClose = durationC;
        if ( durationO < maxOpen )  maxOpen  = durationO;
    }
    
    durationClose = maxClose;
    durationOpen  = maxOpen ;
}

int Mode::get_duration ( bool state ) {
    return ( state ) ? durationClose : durationOpen;
}

void Mode::print_values ( bool state ) {
    ModeOption values = get_stateValues( state );
    for ( short int i = 0; i < FINGER_COUNT; i++ )
        printf( "%d\t\t", values[i][0] );
    printf( "\n" );
}

string Mode::get_stringRepresentation ( ) {
    ostringstream repr;
    repr << "{ name:" << name << ",open:" << modeOptionToString(deactivatedValues, ",") << ",closed:" << modeOptionToString(activatedValues, ",") << " }";
    return repr.str();
}

ModeOption Mode::get_stateValues ( bool state ) {
    return ( state == true ) ? activatedValues : deactivatedValues;
}

void Mode::set_name ( char* mode_name ) { strcpy( name, mode_name ); }

void Mode::set_values ( bool state, ModeOption values ) {
    ModeOption* dest = ( state ) ? &activatedValues : &deactivatedValues;
    dest->swap(values);
    defineDuration();
}

// void Mode::set_values ( bool state, int* values ) {
//     ModeOption* dest = ( state ) ? &activatedValues : &deactivatedValues;
//     for ( int i = 0; i < dest->size(); i++ )
//         for ( int j = 0; j < 3; j++ )
//             dest->at(i).at(j) = values[i][j];
// }