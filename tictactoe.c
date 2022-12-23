#include "tictactoe.h"
#include <stdio.h>
#include <stdbool.h>

bool eval_game(int moves) {
    int i;
    // evalulate rows
    for (i = 0; i < ROW; i++) {
        if (grid_game[i][0] == grid_game[i][1] && grid_game[i][0] == grid_game[i][2])
            return true;
    } 

    // evulate cols
    for (i = 0; i < COL; i++) {
        if (grid_game[0][i] == grid_game[1][i] && grid_game[0][i] == grid_game[2][i])
            return true;
    }

    // evulate diags
    if (grid_game[0][0] == grid_game[1][1] && grid_game[0][0] == grid_game[2][2])
        return true;
    
    if (grid_game[2][0] == grid_game[1][1] && grid_game[1][1] == grid_game[0][2])
        return true;

    if (moves == 9)
        printf("Draw!\n");
    return false;
}

void computer_moves(int moves) {
    
}
