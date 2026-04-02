#include "game.h"
#include "asteroid.h"
#include "config.h"
#include "gpio.h"
#include "uart_hal.h"
#include "ship.h"
#include "timer.h"
#include "utils.h"

volatile board_t game_board;
uint8_t score = 0;
uint8_t level = 1;
volatile bool game_over_flag = false;


void init_board(void) {
    output_string(BOARD);
    ship.x = SHIP_SPAWN_X;
    ship.y = SHIP_SPAWN_Y;
    ship_draw(ship.y, ship.x);
    asteroids_create(&game_board);

    // bullet refresh
    for (uint8_t i = 0; i < MAX_NUM_BULLETS; i++) {
        game_board.bullets[i].x = 0;
        game_board.bullets[i].y = 0;
        game_board.bullets[i].in_frame = false;
    }

    game_board.collision_count = 0;
}

void start_game(void) {
    output_character(CLEAR_SCREEN);
    output_string(hide_cursor);
    init_board();
    output_string(initial_pos);
    output_string(save_pos);
}

void game_over(void) {
    timer_stop();
    delay(100000);
    output_character(CLEAR_SCREEN);
    output_string(prompt_game_over);
    
    char level_str[3];
    int2string(level, level_str);
    output_string("\n\rLevel: ");
    output_string(level_str);
    level++;

    char score_str[6];
    int2string(score, score_str);
    output_string("\n\rScore: ");
    output_string(score_str);
    output_string(show_cursor);
    blink_red_LED();
}
