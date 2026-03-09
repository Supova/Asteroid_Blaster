#ifndef ASSETS_H
#define ASSETS_H

#include <stdbool.h>
#include <stdint.h>

//--------------------STRUCTS--------------------------------------------------------------------------------------
struct position {
    uint8_t x;
    uint8_t y;
};

struct bullet_t {
    // char bullet = "|"
    uint8_t id;
    uint8_t x;
    uint8_t y;
    bool in_frame;
};

struct asteroid_t {
    uint8_t id;
    uint8_t x;
    uint8_t y;
    bool in_frame; // used as flag for active asteroids
};

struct board {
    // array of structs
    struct bullet_t bullets[10];
    struct asteroid_t asteroids[10];
    // score ?
};

struct ship {
    uint8_t x;
    uint8_t y;
    // health ?
};

#endif
