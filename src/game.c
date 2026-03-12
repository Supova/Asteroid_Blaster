#include "game.h"
#include "render.h"
#include "config.h"
#include "utils.h"
#include "ship.h"
#include "asteroid.h"

volatile board_t game_board;

void init_board(void) {
    output_string(BOARD);
    ship_draw(SHIP_SPAWN_Y, SHIP_SPAWN_X);
    asteroids_create(&game_board);
}

void start_game(void) {
    output_character(CLEAR_SCREEN);
    output_string(hide_cursor);
    init_board();
    output_string(initial_pos);
    output_string(save_pos);
}
