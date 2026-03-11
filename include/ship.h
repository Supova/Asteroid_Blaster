#ifndef SHIP_H
#define SHIP_H

#include <stdint.h>
#include "assets.h"

extern volatile ship_t ship;

void ship_draw(uint32_t y, uint32_t x);
void ship_erase(uint32_t y, uint32_t x);
void ship_move_left(volatile ship_t* ship);
void ship_move_right(volatile ship_t* ship);

#endif