#ifndef UTILS_H
#define UTILS_H

#include "assets.h"
#include <stdint.h>

void int2string(uint8_t number, char *string);
void delay(volatile uint32_t seconds);
uint8_t count_active_asteroids(volatile board_t *game_board);

#endif /* UTILS_H */
