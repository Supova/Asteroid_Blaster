#ifndef ASTEROID_H
#define ASTEROID_H

#include "assets.h"
#include <stdbool.h>
#include <stdint.h>

void asteroid_draw(uint32_t y, uint32_t x);
void asteroid_erase(uint32_t y, uint32_t x);
void asteroid_move_all_down(volatile board_t *game_board);
void asteroids_create(volatile board_t *game_board);

#endif /* ASTEROID_H */