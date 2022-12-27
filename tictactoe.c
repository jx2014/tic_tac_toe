#include "tictactoe.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// Function to evulate the current game board.
// If the game is won, provide the winning player.
// int moves is the current game progression. There are total 9 moves available.
bool eval_game(int progression, player_t *winner, bool mute) {
    int i;
    // evaluate rows
    for (i = 0; i < ROW; i++) {
        if (grid_game[i][0] == grid_game[i][1] && grid_game[i][0] == grid_game[i][2]) {
            *winner = (grid_game[i][0] == 'X' ? players[0] : players[1]);
            return true;
        }
    }

    // evaluate cols
    for (i = 0; i < COL; i++) {
        if (grid_game[0][i] == grid_game[1][i] && grid_game[0][i] == grid_game[2][i]) {
            *winner = (grid_game[0][i] == 'X' ? players[0] : players[1]);
            return true;
        }
    }
    
    // evaluate diags
    if (grid_game[0][0] == grid_game[1][1] && grid_game[0][0] == grid_game[2][2]) {
        *winner = (grid_game[1][1] == 'X' ? players[0] : players[1]);
        return true;
    }    
    
    if (grid_game[2][0] == grid_game[1][1] && grid_game[1][1] == grid_game[0][2]) {
        *winner = (grid_game[1][1] == 'X' ? players[0] : players[1]);
        return true;
    }

    if (progression == 9 && !mute)  
        printf("Draw!\n");
    
    return false;
}

bool empty_cell(int cell) {
    return (grid_game[cell/3][cell-1-(cell/3)*3] == (cell + '0') ? true : false);
}

// Function to calculate the score for current game board
// with regards to a target computer player.
// The computer player can be first player, second player, or both players.
// This function is only needed when playing against computer. 
int compute_scores(int progression, player_t target_player) {
    player_t winner;
    bool game_won = eval_game(progression, &winner, true);
    if (game_won && (winner == target_player)) // game won by target computer.
        return 10;
    else if (game_won) // game won by another player.
        return -10;
    else               // game is either still in progress or is draw. No scores given. 
        return 0;
}

// reference: https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/
int minimax(int progression, player_t computer_player, bool isMax, int level) {    
    int i = 0, j = ROW * COL;
    char mark = (progression % 2 == 0) ? 'O' : 'X';
    int score = compute_scores(progression, computer_player);
        
    // game is won.
    if (score == 10) { 
        return score * level;
    } else if (score == -10) {
        return score * level;
    }
    
    if (progression > 9)
        return 0;
    
    //determine computer move or player move
    if (isMax) {
        int best_score = -1000;
        for (int r = 0; r < ROW; r++) {
            for (int c = 0; c < COL; c++) {
                i++;                
                if (isdigit(grid_game[r][c])) {
                    grid_game[r][c] = mark;                    
                    best_score = max(best_score, minimax(++progression, computer_player, !isMax, ++level));
                    grid_game[r][c] = i + '0'; // undo the move
                }
            }
        }  
        return best_score;
    } else {
        int best_score = 1000;
        for (int r = 0; r < ROW; r++) {
            for (int c = 0; c < COL; c++) {   
                i++;          
                if (isdigit(grid_game[r][c])) {
                    grid_game[r][c] = mark;
                    best_score = min(best_score, minimax(++progression, computer_player, !isMax, ++level));
                    grid_game[r][c] = i + '0'; // undo the move
                }
            }
        }
        return best_score;
    }
}

// reference: https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/
int best_move(int progression, player_t computer_player) {
    int best_score = -1000;
    int best_move = 0;
    int move_score = 0;
    int i = 0;

    if (progression < 3 && empty_cell(5))
        return 5;

    for (int r = 0; r < ROW; r++) {
        for (int c = 0; c < COL; c++) {
            i++;
            if (grid_game[r][c] - '0' == i) {
                grid_game[r][c] = (progression % 2 == 0) ? 'O' : 'X';
                move_score = minimax(progression + 1, computer_player, false, 1);
                grid_game[r][c] = i + '0';
                if (best_score == -1000) {
                    best_score = move_score;
                    best_move = i;
                } else if ((best_score < 0 && move_score < 0) || (best_score > 0 && move_score > 0)) { // always lose, then take the longest steps to lose.
                    best_move = (move_score < best_score ? i : best_move);
                    best_score = min(best_score, move_score);
                } else if ((best_score <= 0 && move_score >= 0)) {
                    best_move = (move_score > best_score ? i : best_move);
                    best_score = max(best_score, move_score);
                }
            }
        }
    }
    return best_move; 
}

