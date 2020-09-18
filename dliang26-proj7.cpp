/* dliang26-proj7.cpp
 * Written by Dana Liang for CS 211, Summer 2020
 * 
 * Main code to implement all classes to run the game.
 * 
*/

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

#include "dliang26-Pieces.h"
#include "dliang26-Exceptions.h"
#include "dliang26-Board.h"

int main( int argc, char ** argv ) {
	
	Board * myBoard;
	myBoard = Board::getBoard( );
	myBoard->play( );
	delete myBoard;
	return 0;
	
} // main
