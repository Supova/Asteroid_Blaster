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
    // position_t ne
    asteroids_create(&game_board);
    for (int i=0; i < 10; i++){
        asteroid_draw(game_board.asteroids[i].y,game_board.asteroids[i].x);
        // asteroid_move_down(&game_board.asteroids[i]);
        // asteroid_move_all_down(&game_board);
    }
}

void start_game(void) {
    output_character(CLEAR_SCREEN);
    output_string(hide_cursor);
    init_board();
    output_string(initial_pos);
    output_string(save_pos);
}
