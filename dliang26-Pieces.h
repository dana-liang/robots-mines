/* dliang26-Pieces.h - Header file for the Piece class and all its subclasses.
 * Written by Dana Liang for CS 211, Summer 2020
 */


#ifndef _PIECES_H
#define _PIECES_H

static int nRobots = 0;
// First the Piece class itself

class Piece {
	public:  
		virtual char display( ) = 0;
    	virtual void move( int r, int c );
    	virtual bool isBarrier( );
    	virtual bool isSpace( );
		virtual ~Piece( );
};

// Then all the subclasses

class Player: public Piece {
		virtual char display( );
    	virtual void move( int r, int c );
};


class Robot: public Piece {
		public:
			Robot();
			~Robot();
			static int getNRobots();
			virtual char display( );
			virtual void move( int r, int c );
};


class Mine: public Piece {
		virtual char display( );
};

class Brick: public Piece {
		virtual char display( );
    	virtual bool isBarrier( );
};

class Space: public Piece {
		virtual char display( );
    	virtual bool isSpace( );
};

#endif //_PIECES_H
