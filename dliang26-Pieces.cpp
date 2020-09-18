/* dliang26-Pieces.cpp - Source code file for the Piece class and all its subclasses.
 * Written by Dana Liang for CS 211, Summer 2020
 */

#include "dliang26-Pieces.h"
#include "dliang26-Board.h"
#include "dliang26-Exceptions.h"

// First the Piece class methods

void Piece::move( int r, int c ) {
	return; // Do-nothing method
}

bool Piece::isBarrier() {
	return false; // for most Pieces
}

bool Piece::isSpace() {
	return false; // for most Pieces
}

// Then the Player class methods

char Player::display( ) {
	return 'A';
}

void Player::move( int r, int c ) {
	// Reads in keyboard input
	char move;
	cin >> move;
	move = tolower(move);

	int newRow, newCol;
	// Depending on input, determine where to go.
	switch ( move ) {
		case 'q': { // go diagonally to the upper left corner
			newRow = r - 1;
			newCol = c - 1;
		if ( newRow <0 || newCol < 0 )
				throw InvalidMove( "Can't move there! There's a wall." );
		}
		break;

		case 'w': { // go up
			newRow = r - 1;
			newCol = c;
			if ( newRow < 0 )
				throw InvalidMove( "Can't move there! There's a wall." );
		}
		break;
		
		case 'e': { // go diagonally to the upper right corner
			newRow = r - 1;
			newCol = c + 1;
			if ( newRow < 0 || newCol > 19 )
				throw InvalidMove( "Can't move there! There's a wall." );
		}
		break;

		case 'a': { // go left
			newRow = r;
			newCol = c - 1;
			if ( newCol < 0 )
				throw InvalidMove( "Can't move there! There's a wall." );
		}
		break;

		case 's': { // stay in place: 'S' and any other char
			newRow = r;
			newCol = c;
		}
		break;

		case 'd': { // go right
			newRow = r;
			newCol = c + 1;
			if ( newCol > 19 )
				throw InvalidMove( "Can't move there! There's a wall." );
		}
		break;

		case 'z': { // go diagonally to the bottom left corner
			newRow = r + 1;
			newCol = c - 1;
			if ( newRow > 9 || newCol < 0 )
				throw InvalidMove( "Can't move there! There's a wall." );
		}
		break;

		case 'x': { // go down
			newRow = r + 1;
			newCol = c;
			if ( newRow > 9 )
				throw InvalidMove( "Can't move there! There's a wall." );
		}
		break;

		case 'c': { // go diagonally to the bottom right corner
			newRow = r + 1;
			newCol = c + 1;
			if ( newRow > 9 || newCol > 19 )
				throw InvalidMove( "Can't move there! There's a wall." );
		}
		break;

		default: { // invalid move.
			// will attempt to move more than one space away from the current spot
			throw InvalidMove( "Can't move there! That's more than 1 space." );
		}
	}

	Board* board = Board::getBoard();
	board->moveMeTo( newRow, newCol );
	return;
}

// Then the Robot class methods

Robot::Robot( ) {
	nRobots++;
}

Robot::~Robot( ) {
	nRobots--;
}

int Robot::getNRobots() {
	return nRobots;
}

Piece::~Piece() { }

char Robot::display( ) {
	return 'R';
}

// Basic AI to chase the player
void Robot::move( int r, int c ) {  
	Board* board = Board::getBoard();
	int pRow, pCol; // to hold the player's location
	board->getPlayerPosition( pRow, pCol ); 
	/* robots will try to move diagonally towards the player, then horizontally. */ 
	if ( pRow < r ) {
		r--;
		if ( pCol < c )
			c--;
		else if ( pCol > c )
			c++;
	}
	else if ( pRow > r ) {
		r++;
		if ( pCol < c )
			c--;
		else if ( pCol > c )
			c++;
	}
	else {
		if ( pCol < c )
			c--;
		else if ( pCol > c )
			c++;
	}


	board->moveMeTo( r, c ); // call moveMeTo in the board to actually move the piece
	return;
}

// The Mine class method

char Mine::display( ) {
	return '*';
}

// The Brick class methods

char Brick::display( ) {
	return '#';
}

bool Brick::isBarrier() { // Brick needs to override this one
	return true;
}

// The Space class methods

char Space::display( ) {
	return ' ';
}

bool Space::isSpace() { // Space needs to override this one
	return true;
}


