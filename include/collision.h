#ifndef COLLISION_H
#define COLLISION_H

#include <stdint.h>
#include "assets.h"

void collision_draw(uint32_t y, uint32_t x);
bool collision_check_with_ship_and_asteroid(volatile ship_t ship, volatile board_t *game_board);
void collision_check_with_bullet_and_asteroid(volatile board_t* game_board);


#endif
