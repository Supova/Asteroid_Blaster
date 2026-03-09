#include "game.h"
#include "render.h"
#include "config.h"
#include "utils.h"

void init_board(void) {
    output_string(BOARD);
}

void start_game(void) {
    output_character(CLEAR_SCREEN);
    output_string(hide_cursor);
    init_board();
    output_string(initial_pos);
    output_string(save_pos);
}
