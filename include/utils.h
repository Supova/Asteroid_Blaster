#ifndef UTILS_H
#define UTILS_H

#include "assets.h"
#include <stdbool.h>
#include <stdint.h>

uint8_t simple_read_character(void);
void int2string(uint8_t number, char *string);
void delay(volatile uint32_t seconds);
uint32_t get_random_seed(void);
uint8_t count_active_bullets(volatile board_t *game_board);
uint8_t count_active_asteroids(volatile board_t *game_board);

#endif /* UTILS_H */