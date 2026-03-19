#include "TM4C123.h"
#include "game.h"
#include "asteroid.h"
#include "config.h"
#include "render.h"
#include "ship.h"
#include "timer.h"
#include "utils.h"
#include "gpio.h"

volatile board_t game_board;
volatile uint8_t score = 0;
volatile bool game_over_flag = false;

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

void game_over(void) {
    // timer_stop();
    timer_ticked = false;
    TIMER0->CTL &= ~(1 << 0);
    delay(100000);
    output_character(CLEAR_SCREEN);
    output_string(prompt_game_over);
    char score_str[6];
    int2string((uint32_t)score, score_str);
    output_string(score_str);
    output_string(show_cursor);
    blink_red_LED();
}