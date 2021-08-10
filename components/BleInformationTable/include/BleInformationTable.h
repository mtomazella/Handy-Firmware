#pragma once

#include <string>

using namespace std;

struct InformationTable {
    mutable int     battery_level = 100    ;
    mutable bool    state         = false  ;
    mutable int     mode_index    = 0      ;
    mutable string  mode_name     = "null" ;
};

class BleInformationTable {
    InformationTable table;

public:
    string  getFullStateString ( void );

    int     getBatteryLevel ( void )        {  return table.battery_level;  }
    void    setBatteryLevel ( int level )   {  table.battery_level = level; }
   
    bool    getState        ( void )        {  return table.state;          }
    void    setState        ( bool state )  {  table.state = state;         }
   
    int     getModeIndex    ( void )        {  return table.mode_index;     }
    void    setModeIndex    ( int index )   {  table.mode_index = index;    }
    
    string  getModeName     ( void )        {  return table.mode_name;      }
    void    setModeName     ( string name ) {  table.mode_name = name;      }
};