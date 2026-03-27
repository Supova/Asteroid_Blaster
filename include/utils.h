#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdint.h>
#include "assets.h"

// Function Declarations
// -----------------------------------------------------------------------
uint8_t simple_read_character(void);
void int2string(uint32_t number, char *string);
uint32_t string2int(char *string);
void delay(volatile uint32_t seconds);
uint32_t get_random_seed();
uint8_t count_active_bullets(volatile board_t *game_board);
uint8_t count_active_asteroids(volatile board_t *game_board);

#endif
