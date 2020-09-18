/* dliang26-Exceptions.cpp - Source code file for the Exception class and all its subclasses.
 * Written by Dana Liang for CS 211, Summer 2020
 */

#include "dliang26-Exceptions.h"
#include <string>

// First the methods for Exception itself

Exception::Exception( string s ) {
    
    description = s;

}

Exception::~Exception() {
    
}

string Exception::getDescription( ) {

    return description;
}

// Then the subclasses

InvalidMove::InvalidMove( string s ) : Exception( s ) { // Done as a sample

}

SpaceUnavailable::SpaceUnavailable( string s ) : Exception( s ) {

}

Collision::Collision( string s, int r, int c) : Exception( s ) {

}

