#ifndef ASSETS_H
#define ASSETS_H

#include <stdbool.h>
#include <stdint.h>

// Coordinate system: x = column (horizontal), y = row (vertical)

#define MAX_NUM_BULLETS 20 // does it make sense to keep it here?
#define MAX_NUM_ASTEROIDS 10
#define MAX_NUM_ENTITY 30

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
  //  uint8_t id;
    uint8_t x;
    uint8_t y;
    bool in_frame;
} asteroid_t;

typedef struct entity {
    uint8_t id;
    uint8_t x;
    uint8_t y;
    bool in_frame;
} entity_t;

typedef struct ship {
    uint8_t x;
    uint8_t y;
} ship_t;

typedef struct circbuff {
    entity_t buffer[MAX_NUM_ENTITY];
    uint8_t read;
    uint8_t write;
    uint8_t count;
    uint8_t capacity;
} circbuff_t;

typedef struct board {
    bullet_t bullets[MAX_NUM_BULLETS];
    asteroid_t asteroids[MAX_NUM_ASTEROIDS];
    uint8_t bullet_count;
    uint8_t asteroid_count;
} board_t;

#endif
