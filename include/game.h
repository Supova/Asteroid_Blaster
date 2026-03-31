#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "assets.h"

extern volatile board_t game_board;
extern volatile uint8_t score;
extern volatile bool game_over_flag;
extern uint8_t asteroid_arr_index;

/**
 * @brief Initialize the game board display with ship
 * 
 * Displays the game board ASCII art and draws the player's ship
 * at the starting position.
 */
void init_board(void);

/**
 * @brief Start the game - clear screen and prepare display
 * 
 * Clears terminal, hides cursor, initializes board,
 * and positions cursor at starting location.
 */
void start_game(void);

void game_over(void);

#endif
