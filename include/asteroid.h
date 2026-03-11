#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdint.h>
#include <stdbool.h>
#include "assets.h"

void asteroid_draw(uint32_t y, uint32_t x);
void asteroid_erase(uint32_t y, uint32_t x);
void asteroid_out_of_bounds_check(volatile asteroid_t *asteroid);
void asteroid_move_down(volatile asteroid_t *asteroid);
void asteroid_move_all_down(volatile board_t *game_board);
position_t asteroid_position_randomize();
bool position_taken(position_t pos, volatile board_t *game_board);
void asteroids_create(volatile board_t *game_board);

#endif