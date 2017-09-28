/*
 * tictactoe-main.c
 *
 *  Created on: Jan 18, 2017
 *      Author: phil
 */

#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

static const int COLS = 3;
static const int ROWS = 3;
static const int MIN_POS = 1;
static const int MAX_POS = COLS*ROWS;

/**
 * Get the 0-based row index given a 1-based board position.
 *
 * @param int boardPos a 1-based board position
 * @return a 0-based board row index
 */
static int getRowIndex(int boardPos) {
	return (boardPos-1) / COLS;
}

/**
 * Get the 0-based column index given a 1-based board position.
 *
 * @param int boardPos a 1-based board position
 * @return a 0-based board column index
 */
static int getColIndex(int boardPos) {
	return (boardPos-1) % COLS;
}

/**
 * Main program for an interactive game of tic-tac-toe.
 */
int main(void) {
    Marker** board = createBoard();
    Marker turn = X;

    printf("To play a position use the following map to enter a position.\n");
    printf("-------------\n");
    for (int boardPos = MIN_POS; boardPos <= MAX_POS; boardPos += COLS) {
    	printf("| %d | %d | %d |\n", boardPos, boardPos+1, boardPos+2);
            printf("-------------\n");
    }

    // play until there is a draw or a player has won
    while (!isTie(board) && !hasWon(board, X) && !hasWon(board, O)) {
        int boardPos = -1;
        bool validInput = false;

        // wait for valid input
        while(!validInput) {
            printf("Player %c, enter the position you want to play.\n", toChar(turn));
            int success = scanf("%d", &boardPos);
            if (success < 0 || boardPos < MIN_POS || boardPos > MAX_POS ||
                board[getRowIndex(boardPos)][getColIndex(boardPos)] != EMPTY) {
                continue;
            }
            validInput = true;
        }

        // mark the position and display the updated board
        markTheBoard(board, turn, boardPos);
        printf("%s\n", getBoardDisplay(board));

        switch(turn) {
            case X:
                turn = O;
                break;
            case O:
                turn = X;
                break;
        }
    }

    // game is over so report results
    if (isTie(board)) {
        printf("The game ends in a tie.\n");
    } else if (hasWon(board, X)) {
        printf("Player X has won.");
    } else {
        printf("Player O has won.");
    }

    return EXIT_SUCCESS;
}

