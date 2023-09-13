#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "tic-tac-toe.h"
#include <stdbool.h>

#ifndef _TICTACTOE
#define _TICTACTOE
struct tictactoe {
    char active_player; // the currently active player (either X or O)
    char board[9];      // the board of size 3 x 3 (rows x columns, either X, O, or NONE)
};
#endif // _TICTACTOE

const char X = 'X';
const char O = 'O';
const char NONE = '_';

const int win_length = 3;

const int width = 3;

const int length = 3;

int get_index(const struct tictactoe *t, int row, int col){
    int r = row * 3;
    int index = r + col;
    return index;
}

char get_value(const struct tictactoe *t, int index) {
    return t->board[index];
}

char check_vertical(const struct tictactoe *t) {
    char answer = NONE;
    int count = 0;
    for (int i = 0; i < 3; i = i + 1) {
        for (int j = i; j < 9; j = j + 3) {
            if (t->board[i] != t->board[j]) {
                count = 0;
                break;
            } else {
                count = count + 1;
                if (count == win_length) {
                    break;
                }
            }
        }
        if (count == win_length) {
            answer = t->board[i];
            return answer;
        }
    }
    return answer;
}

char check_horizontal(const struct tictactoe *t) {
    char answer = NONE;
    int count = 0;
    for (int i = 0; i < 7; i = i + 3) {
        for (int j = i; j <= (i + 2); j = j + 1) {
            if (t->board[i] != t->board[j]) {
                count = 0;
                break;
            } else {
                count = count + 1;
                if (count == win_length) {
                    break;
                }
            }
        }
        if (count == win_length) {
            answer = t->board[i];
            return answer;
        }
    }
    return answer;
}

char check_diagonal(const struct tictactoe *t) {
    char answer = NONE;
    int index = get_index(t, 1, 1);
    char middle = get_value(t, index);
    if (t->board[index - 4] == middle && t->board[index + 4] == middle) {
        answer = middle;
    } else if (t->board[index - 2] == middle && t->board[index + 2] == middle) {
        answer = middle;
    }
    return answer;
}

void print_row(struct tictactoe *t, int index) {
    for (int i = index; i < (index + 2); i = i + 1) {
        printf("%c | ", t->board[i]);
    }
    printf("%c\n", t->board[index + 2]);
}

struct tictactoe initialize() {
    struct tictactoe game;

    for (int i = 0; i < width * length; i = i + 1) {
        game.board[i] = NONE;
    }

    game.active_player = X;
    return game;
}

bool do_turn(struct tictactoe *t, int row, int col) {
    assert(row >= 0);
    assert(col >= 0);
    assert(row < length);
    assert(col < width);
    char current = t->active_player;
    int index = get_index(t, row, col);
    if (get_value(t, index) == NONE) {
        if (t->active_player == X) {
            t->board[index] = X;
            t->active_player = O;
        } else {
            t->board[index] = O;
            t->active_player = X;
        }
	return true;
    }
    return false;
}

char has_won(const struct tictactoe *t) {
    char horizontal = check_horizontal(t);
    char vertical = check_vertical(t);
    char diagonal = check_diagonal(t);
    if (horizontal != NONE) {
        return horizontal;
    } else if (vertical != NONE) {
        return vertical;
    } else if (diagonal != NONE) {
        return diagonal;
    } else {
        return NONE;
    }
}

bool has_finished(const struct tictactoe *t) {
    bool answer = true;
    char check = has_won(t);
    for (int i = 0; i < (width * length); i = i + 1) {
        if (t->board[i] == NONE) {
            answer = false;
        }
    }
    if (check == NONE) {
        answer = false;
    } else if (check != NONE) {
	answer = true;
}
    return answer;
}

void tictactoe_print(struct tictactoe *t) {
    assert(t);
    print_row(t, 0);
    printf("---------\n");
    print_row(t, 3);
    printf("---------\n");
    print_row(t, 6);
    printf("it is now %c's turn\n", t->active_player);
}

//main

int main(void) {
    const char START = 'S';
    const char TURN = 'T';
    bool cont = true;

    struct tictactoe game = initialize();

    char input = ' ';
    
    printf("type 'S' to start the game and 'T row col' to do your turn\n");
    printf("use the following diagram as a reference for the coordinates\n");
    printf("0 0 | 0 1 | 0 2\n");
    printf("----------------\n");
    printf("1 0 | 1 1 | 1 2\n");
    printf("----------------\n");
    printf("2 0 | 2 1 | 2 2\n");
		
    while(cont) {
        assert(scanf(" %c", &input) == 1);
        if (input == START) {
            game = initialize();
            tictactoe_print(&game);
        } else  if (input == TURN) {
            int row;
            int col;
            assert(scanf("%d", &row) == 1);
            assert(scanf("%d", &col) == 1);
            bool turn_done = do_turn(&game, row, col);
            if (turn_done) {
                tictactoe_print(&game);
            } else {
                printf("ERROR: Cannot do a turn in row %d, and column %d.\n", row, col);
            }
            if (has_finished(&game)) {
                char winner = has_won(&game);
                if (winner == X) {
                    printf("Congratulation player X, you have won!");
                    cont = false;
                } else if (winner == O) {
                    printf("Congratulation player O, you have won!");
                    cont = false;
                } else if (winner == NONE) {
                    printf("The game has ended in a draw");
                    cont = false;
                } else {
                    printf("ERROR");
                    cont = false;
                }
                exit(0);
            }
        } else if (input != TURN || input != START){
            printf("ERROR: Invalid command");
            exit(0);
        }
    }
}
