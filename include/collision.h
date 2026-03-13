#ifndef COLLISION_H
#define COLLISION_H

#include <stdint.h>
#include <stdbool.h>
#include "assets.h"

void collision_draw(uint32_t y, uint32_t x);
bool collision_check_with_ship_and_asteroid(ship_t ship, asteroid_t asteroid);
void collision_check_with_bullet_and_asteroid(board_t* game_board, asteroid_t *asteroid);


#endif
