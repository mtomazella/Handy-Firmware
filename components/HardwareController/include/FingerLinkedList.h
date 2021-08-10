#pragma once

#include <stdlib.h>
#include "Gpio.h"

class FingerListNode {
public:
    int id = 0;
    Gpio::GpioOutput* output = NULL;
    Gpio::GpioServo*  servo  = NULL;
    FingerListNode* next     = NULL;
};

class FingerLinkedList {
protected:
    FingerListNode* firstNode = NULL;
public:
    void add ( Gpio::GpioServo* element ) {
        FingerListNode* node = new FingerListNode();
        node->servo = element;
        if ( firstNode == NULL ) { 
            firstNode = node; 
            return;
        }
        for ( FingerListNode* i = firstNode; i != NULL; i = i->next ) {
            if ( i->next == NULL ) {
                node->id = i->id + 1;
                i->next = node;
                return;
            } 
        }
    }
    void add ( Gpio::GpioOutput* element ) {
        FingerListNode* node = new FingerListNode();
        node->output = element;
        if ( firstNode == NULL ) { 
            firstNode = node; 
            return;
        }
        for ( FingerListNode* i = firstNode; i != NULL; i = i->next ) {
            if ( i->next == NULL ) {
                node->id = i->id + 1;
                i->next = node;
                return;
            } 
        }
    }
    Gpio::GpioOutput* getOut ( int index ) {
        if ( index < 0 ) return NULL;
        for ( FingerListNode* i = firstNode; i != NULL; i = i->next )
            if ( i->id == index ) return i->output;
        return NULL;
    }
    Gpio::GpioServo* getServo ( int index ) {
        if ( index < 0 ) return NULL;
        for ( FingerListNode* i = firstNode; i != NULL; i = i->next )
            if ( i->id == index ) return i->servo;
        return NULL;
    }
};