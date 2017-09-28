/*
 * This program shows all functions using in tictacto-main.c
 *
 *@author Negin Mortazavi
 *@version 1
 *@since 01-24-2017
 */

#include <stdlib.h>
#include <stdio.h>
#include "tictactoe.h"

/**
 * This function creates a 3x3 array representing a tic tac toe board.
 *
 * @param no parameter(void)
 * @return a pointer of 3x3 array (tic tac toe board) that points to Marker.
 */
Marker **createBoard()
{
	int rows = 3;
	int cols = 3;
	Marker **array2d;

	// allocate an edge array for the rows
	array2d = (Marker**)malloc(rows * sizeof(int*));

	// allocate an array for each row
	for (int row = 0; row < rows; row++) {
		array2d[row] = (Marker*)malloc(cols * sizeof(int));
	}

	// initialize the board to zero.
	for (int row = 0; row < 3; row++){
			for (int col = 0; col < 3; col++)
					array2d[row][col] = EMPTY;
		}

	return array2d;
}

/**
 * This function converts an enum value to an equivalent character.
 *
 * @param Marker m, which is the enum Marker type,
 *        that was defined before and includes either X or O or EMPTY
 * @return character which is equivalent to an entered enum value.
 */
char toChar(Marker m) {

		switch (m)
		{

		case X:
				return 'X';

	    	case O:
	    		return 'O';

	    case EMPTY:
	    		return ' ';

	    default:
	        	return '?'; //should never happen.
	}
}

/**
 * This function returns a string representing a board
 * with the currently populated values.
 *
 * @param Marker** board, which is the pointer by the name of board(2d array)
 *        that points to the Marker.
 * @return a string (strings are naturally acts as pointer) of the
 *         currently populated values for board.
 */

char* getBoardDisplay(Marker** board) {
	int size = 14 * 7 + 1;
	char *printBoard = (char*)malloc(size * sizeof(char*));
	int nch = sprintf(printBoard, "%s", "-------------\n");

	for (int j = 0; j < 3; j++){
	     nch += sprintf(printBoard + nch , "| %c | %c | %c |\n",
	    		 toChar(board[j][0]), toChar(board[j][1]), toChar(board[j][2]));
	     nch += sprintf(printBoard + nch, "-------------\n");
	}

	return printBoard;
}

/**
 * This function takes a position 1-9 and a marker.
 * It places that marker value on the board at the given position
 *
 * @param Marker** board is the pointer by the name of board(2d array)
 *        that points to the Marker.
 * @param int pos is the integer representing the position between 1 and 9.
 * @return nothing (void).
 */

void markTheBoard(Marker** board, Marker m, int pos) {
	int row = (pos-1) / 3;
	int col = (pos-1) % 3;
	board[row][col] = m;
}

/**
 *  This function returns true if the given marker has won the game,
 *  false otherwise.
 *
 * @param Marker** board is the pointer by the name of board(2d array)
 *        that points to the Marker.
 * @param Marker m, which is the enum Marker type,
 *        that was defined before and includes either X or O or EMPTY
 * @return boolean true if the given marker has won the game,
 *         or boolean false otherwise.
 */
bool hasWon(Marker** board, Marker m) {
	bool cond;

	if(((board[0][0] == m) && (board[1][1] == m) && (board[2][2] == m))  ||
       ((board[0][2] == m) && (board[1][1] == m) && (board[2][0] == m))){
        cond = true;
	}
    else{
        for(int row = 0; row < 3; row++){
            if((board[row][0] == m) && (board[row][1] == m) &&
            	(board[row][2] == m)){
            	cond = true;
            }
        }
        for(int col = 0; col < 3; col++){
                    if((board[0][col] == m) && (board[1][col] == m) &&
                    	(board[2][col] == m)){
                    	cond = true;
                    }
        }
    }

    return cond;
}

/**
 *  This function returns true if the given board is a tie, false otherwise.
 *
 * @param Marker** board is the pointer by the name of board(2d array)
 *        that points to the Marker.
 * @return boolean true if the given board is a tie,
 * 	       or boolean false otherwise.
 */
bool isTie(Marker** board) {
	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			if (board[row][col] == EMPTY){
				return false;
			}
		}
	}
	return !(hasWon(board, X) || hasWon(board, O));
}
