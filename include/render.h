#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include "assets.h"

void output_character(char c);
void output_string(const char *str);
void cursor_goto(uint32_t y, uint32_t x);
void render_game_entities(volatile board_t *game_board, volatile ship_t ship);

#endif /* RENDER_H */