#include "tictactoe.h"
#include <stdio.h>
#include <stdbool.h>

// Function to evulate the current game board.
// If the game is won, provide the winning player.
// int moves is the current game progression. There are total 9 moves available.
bool eval_game(int moves, player_t *winner) {
    int i;
    // evalulate rows
    for (i = 0; i < ROW; i++) {
        if (grid_game[i][0] == grid_game[i][1] && grid_game[i][0] == grid_game[i][2]) {
            *winner = grid_game[i][0] == 'X' ? players[0] : players[1]
            return true;
        }
    }

    // evulate cols
    for (i = 0; i < COL; i++) {
        if (grid_game[0][i] == grid_game[1][i] && grid_game[0][i] == grid_game[2][i]) {
            *winner = grid_game[0][i] == 'X' ? players[0] : players[1]
            return true;
        }
    }
    
    // evulate diags
    if (grid_game[0][0] == grid_game[1][1] && grid_game[0][0] == grid_game[2][2]) {
        *winner = grid_game[1][1] == 'X' ? players[0] : players[1]
        return true;
    }    
    
    if (grid_game[2][0] == grid_game[1][1] && grid_game[1][1] == grid_game[0][2]) {
        *winner = grid_game[1][1] == 'X' ? players[0] : players[1]
        return true;
    }

    if (moves == 9)  
        printf("Draw!\n");
    
    return false;
}

// Function to calculate the score for current game board
// with regards to a target player.
// This function is only needed when playing against computer. 
int compute_scores(int moves, player_t target_player) {
    player_t *winner;
    bool game_won = eval_game(moves, &winner);
    if (game_won && *winner == target_player) // game won by target computer.
        return 10;
    else if (game_won) // game won by another player.
        return -10;
    else               // game is either still in progress or is draw. No scores given. 
        return 0;
}

int minmax(int progression) {

}

