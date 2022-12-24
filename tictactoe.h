#include <stdbool.h>

#ifndef TICTACTOE_H
#define TICTACTOE_H

#define ROW 3
#define COL 3
#define GRID_ROW 5
#define GRID_COL 11

typedef enum {PLAYER1 = 0, PLAYER2, COMPUTER, COMPUTER2} player_t;

extern int grid_lookup[];
extern char grid_game[][COL];
extern player_t players[];
extern char *players_s[];

void set_players(void);
void initialize_game(void);
void print_grid(void);
bool make_a_move(int progression);
bool eval_game(int progression, player_t *player);

bool computer_make_a_move(int progression, int move);

#endif