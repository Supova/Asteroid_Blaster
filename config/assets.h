#ifndef ASSETS_H
#define ASSETS_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_NUM_BULLETS 20
#define MAX_NUM_ASTEROIDS 10

// Coordinate system: x = column (horizontal), y = row (vertical)
typedef struct position {
    uint8_t x;
    uint8_t y;
} position_t;

typedef struct bullet {
    uint8_t x;
    uint8_t y;
    bool in_frame;
} bullet_t;

typedef struct asteroid {
    uint8_t x;
    uint8_t y;
    bool in_frame;
} asteroid_t;

typedef struct ship {
    uint8_t x;
    uint8_t y;
} ship_t;

typedef struct collision_event {
    uint8_t x;
    uint8_t y;
} collision_event_t;

typedef struct board {
    bullet_t bullets[MAX_NUM_BULLETS];
    asteroid_t asteroids[MAX_NUM_ASTEROIDS];
    uint8_t asteroid_count;
    collision_event_t collisions[MAX_NUM_ASTEROIDS];  // Max collisions visible
    uint8_t collision_count;
} board_t;

#endif /* ASSETS_H */