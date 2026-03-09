#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdint.h>

#include "assets.h"


// Globals
extern const char *BOARD;
extern volatile struct board game_board;

// Function Declarations -----------------------------------------------------------------------
uint8_t simple_read_character(void);
void int2string(uint32_t number, char *string);
uint32_t string2int(char *string);



#endif
