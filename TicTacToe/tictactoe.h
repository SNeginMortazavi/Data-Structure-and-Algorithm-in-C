/**
 * Functions and types to implement the game of tic-tac-toe.
 *
 */
#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <stdbool.h>

/**
 * A cell is marked X, 0, or is EMPTY
 */
typedef enum {
    X,
    O,
    EMPTY
} Marker;


/**
 *  This function creates a 3x3 array representing a tic tac toe board.
 */
Marker ** createBoard();

/**
 * This function returns a string representing a board with the currently populated values.
 */
char* getBoardDisplay(Marker** board);

/**
 * This function takes a position 1-9 and a marker. It places that marker value on the board
 * at the given position
 */
void markTheBoard(Marker** board, Marker m, int pos);

/**
 * This function returns true if the given marker has won the game, false otherwise.
 */
bool hasWon(Marker** board, Marker m);

/**
 * This function converts an enum value to an equivalent character.
 */
char toChar(Marker m);

/**
 * This function returns true if the given board is a tie, false otherwise.
 */
bool isTie(Marker** board);

#endif
