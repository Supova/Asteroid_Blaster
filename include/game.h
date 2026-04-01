#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "assets.h"

extern volatile board_t game_board;
extern volatile uint8_t score;
extern volatile bool game_over_flag;

void init_board(void);
void start_game(void);
void game_over(void);

#endif
