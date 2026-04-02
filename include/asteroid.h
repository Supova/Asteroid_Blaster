#ifndef ASTEROID_H
#define ASTEROID_H

#include "assets.h"
#include <stdbool.h>
#include <stdint.h>

void asteroid_draw(uint32_t y, uint32_t x);
void asteroid_erase(uint32_t y, uint32_t x);
void asteroid_move_all_down(volatile board_t *game_board);
void asteroids_create(volatile board_t *game_board);
bool position_taken(position_t pos, volatile board_t *game_board);
void asteroid_out_of_bounds_check(volatile asteroid_t *asteroid);
void asteroid_move_down(volatile asteroid_t *asteroid);
position_t asteroid_position_randomize(void);

#endif /* ASTEROID_H */