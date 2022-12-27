#include "tictactoe.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

player_t winner;
int progression;
int computer_move;

int main(void) {
    srand((unsigned) time(NULL));

    while (true) {        
        // Game start
        initialize_game();
        set_players();
        // test code:
        /*grid_game[][] = {
                         {'1', 'X', '3'},
                         {'4', '5', 'X'},
                         {'O', 'O', 'X'}
                         };*/
        //grid_game[0][1] = grid_game[0][2] = grid_game[1][1] = 'X';
        //grid_game[0][0] = grid_game[2][1] = 'O';
        int test_progression = 1;
        print_grid();


        for (progression = test_progression; progression <= 9; progression++) {
            if (progression % 2 == 0 && players[1] == COMPUTER2) {
                printf("Computer2's move.\n");
                computer_move = best_move(progression, COMPUTER2);
                computer_make_a_move(progression, computer_move);
            } else if ((progression % 2 == 0 ? players[1] : players[0]) == COMPUTER) {
                printf("Computer's move.\n");
                computer_move = best_move(progression, COMPUTER);
                computer_make_a_move(progression, computer_move);
            } else {
                while (!make_a_move(progression)) {
                    printf("Illegal move, try again.\n");
                }
            }
            print_grid();
            if (progression > 4) {
                if (eval_game(progression, &winner, false)) {
                    printf("Game is won by %s!\n",                                  \
                        players_s[winner]);
                    break;
                }
            }
        }        
    }

    return 0;
}