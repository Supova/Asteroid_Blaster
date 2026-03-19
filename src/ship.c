#include "ship.h"
#include "TM4C123.h"
#include "config.h"
#include "render.h"

volatile ship_t ship = {SHIP_SPAWN_X, SHIP_SPAWN_Y};

void ship_draw(uint32_t y, uint32_t x) {
    cursor_goto(y, x);
    output_string(SHIP_SYMBOL);
}

void ship_erase(uint32_t y, uint32_t x) {
    cursor_goto(y, x);
    output_string(BLANK);
}

void ship_move_left(volatile ship_t *ship) {
    __disable_irq();
    if (ship->x > PLAYABLE_MIN_X) {
        ship_erase(ship->y, ship->x);
        (ship->x)--;
        ship_draw(ship->y, ship->x);
    }
    __enable_irq();
}

void ship_move_right(volatile ship_t *ship) {
    __disable_irq();
    if (ship->x < PLAYABLE_MAX_X) {
        ship_erase(ship->y, ship->x);
        (ship->x)++;
        ship_draw(ship->y, ship->x);
    }
    __enable_irq();
}
