#ifndef ASSETS_H
#define ASSETS_H

#include <stdbool.h>
#include <stdint.h>

typedef struct position {
    uint8_t x;
    uint8_t y;
} position_t;

typedef struct bullet {
    uint8_t id;
    uint8_t x;
    uint8_t y;
    bool in_frame;
} bullet_t;

typedef struct asteroid {
    uint8_t id;
    uint8_t x;
    uint8_t y;
    bool in_frame;
} asteroid_t;

typedef struct ship {
    uint8_t x;
    uint8_t y;
} ship_t;

typedef struct board {
    bullet_t bullets[10];
    asteroid_t asteroids[10];
} board_t;

#endif
