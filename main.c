#include "tictactoe.h"
#include <stdio.h>
#include <stdbool.h>


int main(void) {
   
    while (true) {        
        // Game start
        initialize_game();
        set_players();
        print_grid();

        for (int i = 1; i <= 9; i++) {
            if ((i % 2 == 0 ? players[1] : players[0]) == COMPUTER) {
                printf("Computer's move. TBD.\n");
            } else {
                while (!make_a_move(i)) {
                    printf("Illegal move, try again.\n");
                }
            }
            print_grid();
            if (i > 4)
                if (eval_game(i)) {
                    printf("Game is won by %s!\n",                                  \
                            players_s[(i % 2 == 0 ? players[1] : players[0])]);
                    break;
                }
        }        
    }

    return 0;
}