/* dliang26-Board.cpp
 * Written by Dana Liang for CS 211, Summer 2020
 * 
 * Actual code for Board objects:
 *      - assigning values to all Board variables
 *      - returning pointers to Board instances
 *      - display the board
 *      - allow moves to be played and pieces to be moved
 *      - exception handling for when the pieces collide and when the game ends
*/


#include "dliang26-Board.h"
#include "dliang26-Exceptions.h"

Board * Board::theBoard = NULL;

// Board Constructor
Board::Board( ) {
    // set the size of the board
    nRows = 10;
    nCols = 20;

    // initialize all pointers to null and the lastTurn array all to 0
    for ( row = 0; row < nRows; row++ ) {
        for ( col = 0; col < nCols; col++ ) {
            pieces[row][col] = NULL;
            lastTurnPlayed[row][col] = 0;
        }
    }
    currentTurn = 1; // 1 higher than lastTurn
    
    // assign random spots to all pieces
    srand(time(0));
    //5-10 robots
    for ( int nRobots = 0 ; (nRobots < rand() % 2 + 5); nRobots++ ) {
        row = rand() % nRows;
        col = rand() % nCols;
        pieces[row][col] = new Robot();
    }

    // 0-8 mines
    for ( int nMines = 0; (nMines < rand() % 9); nMines++ ) {
        row = rand() % nRows;
        col = rand() % nCols;
        pieces[row][col] = new Mine();
    }

    // 0-8 bricks
    for ( int nBricks = 0; (nBricks < rand() % 9); nBricks++ ) {
        row = rand() % nRows;
        col = rand() % nCols;
        pieces[row][col] = new Brick();
    }

    // begin player in random spot on the board
    playerRow = rand() % nRows;
    playerCol = rand() % nCols;
    pieces[playerRow][playerCol] = new Player();  

    #ifdef DEBUG
    // test barrier exception, put a brick next to the player
    pieces[playerRow][playerCol-1] = new Brick();
    // test collision exception, put a mine next to the player
    pieces[playerRow][playerCol+1] = new Mine();
    #endif

    // rest of the spots are spaces
    for ( row = 0; row < nRows; row++ ) {
        for ( col = 0; col < nCols; col++ ) {
            if ( pieces[row][col] == NULL )
                pieces[row][col] = new Space();
        }
    }
} //Board::Board()

// Return a pointer to the instance of the board
Board * Board::getBoard( ) {
    if ( theBoard == NULL )
        theBoard = new Board();
    
    return theBoard;
}

// Display the board
void Board::display( ) {
    // Print top border
    cout << '+';
    for ( col = 0; col < nCols; col++ )
        cout << '=';
    cout << '+' << endl;
    
    // Print pieces array and side borders
    for ( row = 0; row < nRows; row++ ) {
        cout << '|';
        for ( col = 0; col < nCols; col++ ) {
            cout << pieces[row][col]->display();
        }
        cout << '|' << endl;
    }
    
    // Print bottom border
    cout << '+';
    for ( col = 0; col < nCols; col++ )
        cout << '=';
    cout << '+' << endl;

    // Print instructions
    cout << "Make a move with:\n"
		 << "Q  W  E\n"
		 << "A  S  D\n"
		 << "Z  X  C\n"
		 << "where the letters are the directions to go and 'S' is to stay in place." << endl;
}

// Gameplay
void Board::play( ) {
    bool done = false;
    while (!done) {
        display(); //display the board
        try { // player moves first.
            row = playerRow;
            col = playerCol;
            pieces[playerRow][playerCol]->move(playerRow, playerCol);
        }
        
        catch ( SpaceUnavailable sUnavailable ) { // if space is unavailable
            cout << "Exception caught: " << sUnavailable.getDescription() << endl
                << "Try again." << endl;
            continue;
        }

        catch (  InvalidMove invalid ) { // if move is invalid
            cout << "Exception caught: " << invalid.getDescription() << endl
                << "Try again." << endl;
            continue;
        }

        catch ( Collision collision ) { // if player collides into a robot or mine
            cout << "CRASH!!! " << collision.getDescription() << endl;
            cout << "GAME OVER. Exiting..." << endl;
            break;
        }

        for ( row = 0; row < nRows; row++ ) {
            for ( col = 0; col < nCols; col++ ) {
                if ( lastTurnPlayed[row][col] < currentTurn ) { // if they haven't moved
                    try { // robots will move here.
                            pieces[row][col]->move( row, col );
                    }
                    catch ( Collision collision ) { // if robot collides into anything
                        cout << "Robot collision! " << collision.getDescription() << endl;
                        if ( collision.getDescription() == "A robot got you! You lose :(" ) {
                            cout << "GAME OVER. Exiting..." << endl;
                            done = true;
                            break;
                        } // endIF
                    } //end catch(Collision)
                } // end if (lastTurnPlayed[row][col])
            } // end inside for loop
        } // end for loop
        currentTurn++;

        if ( Robot::getNRobots() == 0 ) {
            cout << "All robots destroyed! Congratulations! You win!" << endl;
            cout << "GAME OVER. Exiting..." << endl;
            done = true;
        }
    } // end while(!done)
}// end Board::play()

// Function to move pieces
void Board::moveMeTo( int newRow, int newCol ) {
    if ( pieces[row][col]->display() == 'R' ) { //if piece to move is a robot
        if ( pieces[newRow][newCol]->display() == '*' ) { // robot crashes into a mine
            delete pieces[row][col]; // delete the piece that crashed
            pieces[row][col] = new Space(); // replace it with a space
            lastTurnPlayed[newRow][newCol] = currentTurn; // this robot has taken a turn.
            throw Collision( "Crashed into a Mine!", newRow, newCol ); 
            }

        else if ( pieces[newRow][newCol]->display() == 'A' ) { // robot crashes into the player
            delete pieces[newRow][newCol]; // delete the one being collided into
            pieces[newRow][newCol] = new Robot(); // replace it with a robot
            delete pieces[row][col]; // delete the one that crashed
            pieces[row][col] = new Space(); //replace it with a space
            lastTurnPlayed[newRow][newCol] = currentTurn; // this robot has taken a turn.
            throw Collision( "A robot got you! You lose :(", newRow, newCol );
        }

        else if ( pieces[newRow][newCol]->display() == 'R' ) { // robot crashes into a robot
            delete pieces[newRow][newCol]; // delete the one being collided into
            pieces[newRow][newCol] = new Mine(); // replace it with a mine
            delete pieces[row][col]; // delete the one that crashed
            pieces[row][col] = new Space(); //replace it with a space
            lastTurnPlayed[newRow][newCol] = currentTurn; // this robot has taken a turn.
            throw Collision( "Crashed into each other!", newRow, newCol );
        }

        else if ( pieces[newRow][newCol]->display() == '#' ) { // robot crashes into a brick
            lastTurnPlayed[newRow][newCol] = currentTurn; // this robot has taken a turn.
        }

        else {
            delete pieces[row][col]; //delete robot in the old spot
            delete pieces[newRow][newCol];	//delete space in the new spot
            pieces[newRow][newCol] = new Robot();
            pieces[row][col] = new Space();
            lastTurnPlayed[newRow][newCol] = currentTurn; // this robot has taken a turn.
        }
    }

    // if piece to move is the player, and they are not staying in place
    else if ( playerRow != newRow || playerCol != newCol ) {
        if ( pieces[newRow][newCol]->isBarrier() ) 
            // if it's a brick
            throw SpaceUnavailable( "It's a brick." );
        if ( pieces[newRow][newCol]->display() == 'R' )
            throw Collision( "You walked into a robot! You lose :(", newRow, newCol );
        else if ( pieces[newRow][newCol]->display() == '*' )
            throw Collision( "You walked into a mine! You lose :(", newRow, newCol );
        
        
        /* actually make the move */
        delete pieces[playerRow][playerCol]; // delete player in the old spot
        delete pieces[newRow][newCol]; // delete space in the new spot
        pieces[newRow][newCol] = new Player(); // set new spot to the player
        pieces[playerRow][playerCol] = new Space(); // set old spot to a space
        playerRow = newRow; // update row
        playerCol = newCol; // update col
        lastTurnPlayed[playerRow][playerCol] = currentTurn; // the player has taken a turn.
    }
    
    else { // if the player is staying in place
        lastTurnPlayed[playerRow][playerCol] = currentTurn; // the player has taken a turn.
    }
    
}

// Get the player's position for robots to move
void Board::getPlayerPosition( int & row, int & col ) {
    row = playerRow;
    col = playerCol;
}