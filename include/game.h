#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "assets.h"

extern volatile board_t game_board;

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

#endif
