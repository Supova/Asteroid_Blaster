#ifndef BULLETS_H
#define BULLETS_H

#include "assets.h"
#include <stdbool.h>
#include <stdint.h>

void bullet_draw(uint32_t y, uint32_t x);
void bullet_erase(uint32_t y, uint32_t x);
void bullet_spawn(volatile board_t *board, uint8_t y, uint8_t x);
void bullet_move_all_up(volatile board_t *game_board);
void bullet_move_up(volatile bullet_t *bullet);
void bullet_out_of_bounds_check(volatile bullet_t *bullet);

#endif /* BULLETS_H */