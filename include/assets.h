#ifndef ASSETS_H
#define ASSETS_H

#include <stdbool.h>
#include <stdint.h>

// Coordinate system: x = column (horizontal), y = row (vertical)

#define MAX_NUM_BULLETS 3 // does it make sense to keep it here?
#define MAX_NUM_ASTEROIDS 3

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
    bullet_t bullets[MAX_NUM_BULLETS];
    asteroid_t asteroids[MAX_NUM_ASTEROIDS];
    uint8_t bullet_count;
} board_t;

#endif
