#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "Hand.h"
#include "StorageController.h"

int Hand::addMode ( Mode* newMode ) {
    for ( short int i = 0; i < MODE_COUNT; i++ ) {
        if ( modes[i] == NULL ){
            modes[i] = newMode;
            if ( currentMode == NULL ) currentMode = newMode;
            return i;
        } 
    }
    return -1;
}

void Hand::clearModes ( void ) {
    for ( int i = 0; i < MODE_COUNT; i++ ) modes[i] = NULL;
}

void Hand::switchMode ( void ) {
    int newIndex = currentModeIndex;
    for ( short int i = currentModeIndex; i <= MODE_COUNT; i++ ) {
        newIndex = (i+1>=MODE_COUNT)?0:i+1;
        if ( modes[newIndex] != NULL ) {
            cout << "\n" << modes[newIndex]->get_stringRepresentation() << "\n";
            currentMode = modes[newIndex];
            currentModeIndex = newIndex;
            break;
        }
    }
}


int* stringVectorToIntArray ( std::vector<std::string> vector ) {
    int* array = (int*) malloc( sizeof( int ) * FINGER_COUNT );
    for ( int i = 0; i < FINGER_COUNT; i++ ) {
        array[i] = std::stoi( vector[i] );
    }
    return array;
}

std::vector<std::string> splitString(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

void Hand::initFromModesString ( std::string modes ) {
    clearModes();
    std::vector<std::string> modeList = splitString( modes, '|' );
    for ( int i = 0; i < modeList.size(); i++ ) {
        std::vector<std::string> members = splitString( modeList[i], ';' );
        std::string name = members[0];
        std::vector<std::string> openVector   = splitString( members[1], ',' );
        std::vector<std::string> closedVector = splitString( members[2], ',' );
        ModeOption openState;
        ModeOption closedState;
        for ( int j = 0; j < openVector.size(); j++ ) {
            std::vector<std::string> open2 = splitString( openVector[j], '.' );
            ModeOptionState state = {0,0,0};
            for ( int k = 0; k < open2.size() && k < 3; k++ )
                state.at(k) = stoi( open2[k] );
            openState.at(j).swap( state );
        }
        for ( int j = 0; j < openVector.size(); j++ ) {
            std::vector<std::string> closed2 = splitString( closedVector[j], '.' );
            ModeOptionState state = {0,0,0};
            for ( int k = 0; k < closed2.size() && k < 3; k++ )
                state.at(k) = stoi( closed2[k] );
            closedState.at(j).swap( state );
        }
        addMode( new Mode( (char*)name.c_str(), (ModeOption)openState, (ModeOption)closedState ) );
    }
}

void Hand::initModes ( StorageController* storage ) {
    std::string modes = storage->read( "modes" );
    std::cout << "\n" << modes << "\n";
    if ( modes.compare( "" ) != 0 ) initFromModesString( modes );
}