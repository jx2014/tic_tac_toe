#include "tictactoe.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

// Lookup table to map printed grid to game grid
// mapping number 1 5 9 to 0 1 2 for row, and 0 2 4 to 0 1 2 for col
//                   0 1 2 3 4 5 6 7 8 9 
int grid_lookup[] = {0,0,1,0,2,1,0,0,0,2};

char grid_game[ROW][COL];

// An array holding two players.
// A player is defined by enum PLAYER1 = 0, PLAYER2 = 1, COMPUTER = 2, COMPUTER2 = 3.
player_t players[2];

// Array of players in string representation.
// Elements are "Player 1", "Player 2", "Computer"
char *players_s[] = {"Player 1", "Player 2", "Computer", "Computer2"};

void set_players(void) {
    printf("\n");
    printf("Select game mode (1 - 4): \n");
    printf("1. Player 1 vs Player 2\n");
    printf("2. Player 1 vs Computer, Player 1 first move\n");
    printf("3. Player 1 vs Computer, Computer first move\n");
    printf("4. Computer vs Computer.\n");
    printf("Enter q or Q to exit the game.\n");
    int m = 0;
    while (true) {
        m = getchar();
        while(fgetc(stdin) != '\n');
        if (m == 'q' || m == 'Q')
            exit(EXIT_SUCCESS);
        m = m - '0';
        if (m >= 1 && m <= 4)
            break;
        printf("Invalid selection.\n");        
    }
    switch (m) {
        case 1:
            players[0] = PLAYER1;
            players[1] = PLAYER2;
            printf("Player 1 vs Player 2\n");
            break;
        case 2:
            players[0] = PLAYER1;
            players[1] = COMPUTER;
            printf("Player 1 vs Computer\n");
            break;
        case 3:
            players[0] = COMPUTER;
            players[1] = PLAYER2;
            printf("Computer vs Player 2\n");
            break;
        case 4:
            players[0] = COMPUTER;
            players[1] = COMPUTER2;
            printf("Computer vs Computer 2\n");
            break;
    }
}

// Function to reset the game board.
void initialize_game(void) {
    int i = 1, row, col;
    for (row = 0; row < ROW; row++) {
        for (col = 0; col < COL; col++) {
            grid_game[row][col] = '0' + i++;
        }
    }
}

// Function to print out current game board.
void print_grid(void) {
    int row, col;
    printf("\n");
    for (row = 0; row < GRID_ROW; row++) {
        printf("                    ");
        for (col = 0; col < GRID_COL; col++) {
            if (col == 3 || col == 7)
                printf("|");
            else if (row == 1 || row == 3)
                printf("-");            
            else if ((row == 0 || row == 2 || row == 4) && \
                     (col == 1 || col == 5 || col == 9)) {
                printf("%c", grid_game[grid_lookup[row]][grid_lookup[col]]);
            } else
                printf(" ");
        }
        printf("\n");
    }
}

// manually making a move by typing 1 to 9 on the grid. 
bool make_a_move(int progression) {
    int row, col, move;
    char mark = (progression % 2 == 0 ? 'O' : 'X');
    printf("%s's turn.\n", players_s[(progression % 2 == 0 ? players[1] : players[0])]);
    printf("Enter a move (1 - 9) for \'%c\': ", mark);
    move = fgetc(stdin);
    while(fgetc(stdin) != '\n');
    
    if (move == 'q' || move == 'Q')
        exit(EXIT_SUCCESS);

    move = move - '0';
    if (move > 9 || move < 1)
        return false;
    
    cell_to_board(move, &row, &col);
    if (!empty_cell(move))
        return false;
    grid_game[row][col] = mark;
    return true;  
}

// Function used by computer to make a move
void computer_make_a_move(int progression, int move) {
    int row, col;
    cell_to_board(move, &row, &col);
    if (empty_cell(move))
        grid_game[row][col] = (progression % 2 == 0 ? 'O' : 'X');
}

bool empty_cell(int cell) {
    if (cell < 1 || cell > 9)
        return false;
    int row, col;
    cell_to_board(cell, &row, &col);
    return (grid_game[row][col] == (cell + '0') ? true : false);
}

// function to convert cell 1 to 9 to row and col
void cell_to_board(int cell, int * row, int * col) {
    // row * 3 + col + 1 = cell;
    // row = (cell - 1) / 3; 
    // col = (cell - 1) - row * 3;
    *row = (cell - 1) / 3;
    *col = (cell - 1) - *row * 3;
}