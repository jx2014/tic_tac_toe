#include <stdbool.h>

#ifndef TICTACTOE_H
#define TICTACTOE_H

#define ROW 3
#define COL 3
#define GRID_ROW 5
#define GRID_COL 11

#define max(x, y) ({ __typeof__ (x) _x = (x); \
                     __typeof__ (y) _y = (y); \
                     _x > _y ? _x : _y; })

#define min(x, y) ({ __typeof__ (x) _x = (x); \
                     __typeof__ (y) _y = (y); \
                     _x < _y ? _x : _y; })


typedef enum {PLAYER1 = 0, PLAYER2, COMPUTER, COMPUTER2} player_t;

extern int grid_lookup[];
extern char grid_game[][COL];
extern player_t players[];
extern char *players_s[];

// thse are basic functions that interface with the games
void set_players(void);
void initialize_game(void);
void print_grid(void);
bool make_a_move(int progression);
void computer_make_a_move(int progression, int move);
bool empty_cell(int cell);
void cell_to_board(int cell, int * row, int * col);

// compute automated moves.
bool eval_game(int progression, player_t *player, bool mute);
// int compute_scores(int progression, player_t target_player);
// int minimax(int progression, player_t computer_player, bool isMax);
int best_move(int progression, player_t computer_player);


#endif