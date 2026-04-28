#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "assets.h"

extern volatile board_t game_board;
extern uint8_t score;
extern uint8_t hits_this_level;

void start_game(void);
void game_over(void);
void next_level(void);

#endif /* GAME_H */
