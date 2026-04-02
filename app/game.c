#include "game.h"
#include "asteroid.h"
#include "config.h"
#include "gpio.h"
#include "uart.h"
#include "uart_hal.h"
#include "ship.h"
#include "timer.h"
#include "utils.h"

volatile board_t game_board;
uint8_t score = 0;
uint8_t level = 1;
uint8_t hits_this_level = 0;

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
    hits_this_level = 0;
}

void start_game(void) {
    output_character(CLEAR_SCREEN);
    output_string(hide_cursor);
    init_board();
    output_string(initial_pos);
    output_string(save_pos);
}

static void display_level(void) {
    char level_str[3];
    int2string(level, level_str);
    output_string("\n\rLevel: ");
    output_string(level_str);
}

static void display_score(void) {
    char score_str[6];
    int2string(score, score_str);
    output_string("\n\rScore: ");
    output_string(score_str);
}

void game_over(void) {
    timer_stop();
    delay(100000);
    output_character(CLEAR_SCREEN);
    output_string(prompt_game_over);
    display_level();
    display_score();
    blink_red_LED();
    
    // Reset everything for a fresh game
    score = 0;
    level = 1;
    timer0_period_ticks = 16000000;
    
    output_string("\n\r");
    output_string(prompt_restart);
    output_string(show_cursor);
    uint8_t response = ' ';
    while (response != 'y') {
        response = uart_read_blocking();
    }

    timer_change_speed(timer0_period_ticks);
    start_game();
}

void next_level(void) {
    timer_stop();
    delay(100000);
    output_character(CLEAR_SCREEN);
    output_string(prompt_level_complete);
    display_level();
    display_score();

    level++;
    timer0_period_ticks /= 2;

    delay(3000000);

    timer_change_speed(timer0_period_ticks);
    start_game();
}
