#include <stdbool.h>

#ifndef _TICTACTOE
#define _TICTACTOE
struct tictactoe {
    char active_player; // the currently active player (either X or O)
    char board[9];      // the board of size 3 x 3 (rows x columns, either X, O, or NONE)
};
#endif // _TICTACTOE

//represents the player X
extern const char X;

//represents the player O
extern const char O;

//represents neither of the players
extern const char NONE;

//starts a tictactoe game with an empty board and X as the active player
struct tictactoe initialize();

// do_turn(t, row, col) attempts to do a turn for the current player by placing an
//      x or o in the correspending row x col. The function changes the active player 
//      and returns true if the turn was successful, otherwise it does not change the
//      active player returns false.
//  effects: might mutate *t
//  requires: row and colmmust be valid
bool do_turn(struct tictactoe *t, int row, int col);

// has_finished(t) returns true if the game has finished and false otherwise
bool has_finished(const struct tictactoe *t);

// has_won(t) returns the player that has won or NONE if noone has won
char has_won(const struct tictactoe *t);

// tictactoe_print(t) prints out the current board
//  effects: prints output
void tictactoe_print(struct tictactoe *t);