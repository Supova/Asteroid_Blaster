#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include "assets.h"

void render_game_entities(volatile board_t *game_board, volatile ship_t ship);

#endif /* RENDER_H */
