/* dliang26-Board.h - Header file for the Board class
 * Written by Dana Liang for CS 211, Summer 2020
 * 
 * This declares the data fields and methods to be included in Board objects.
 */


#ifndef _BOARD_H
#define _BOARD_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


#include "dliang26-Pieces.h"

#define NROWS 10
#define NCOLS 20

class Board {
	private: 
	    int nRows;
	    int nCols;
	    int row;
	    int col;
	    int playerRow;
	    int playerCol;
	    Piece * pieces[ NROWS ][ NCOLS ];
	    int lastTurnPlayed[ NROWS ][ NCOLS ];
	    int currentTurn;
	    static Board * theBoard;
		Board( ); // PRIVATE constructor, for Singleton pattern
	    
	public: 
		static Board * getBoard( );
		void display( );
		void play( );
		void moveMeTo( int newRow,  int newCol );
		void getPlayerPosition( int & row, int & col );
};

#endif //_BOARD_H
