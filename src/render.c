#include "render.h"
#include "TM4C123.h"
#include "asteroid.h"
#include "bullet.h"
#include "collision.h"
#include "config.h"
#include "ship.h"
#include "utils.h"

void output_character(char c) {
    while (UART0->FR & (1 << 5))
        ;          // WAIT (block) while TX FIFO is full
    UART0->DR = c; // Write char when FIFO has space
}

void output_string(const char *str) {
    while (*str) {
        output_character(*str++);
    }
}

void cursor_goto(uint32_t y, uint32_t x) {
    char buf[20];
    uint8_t index = 0;

    buf[index++] = '\x1B';
    buf[index++] = '[';

    // Append Y coordinate
    char temp[12];
    int2string(y, temp);
    for (uint8_t i = 0; temp[i] != '\0'; i++) {
        buf[index++] = temp[i];
    }

    buf[index++] = ';';

    // Append X coordinate
    int2string(x, temp);
    for (uint8_t i = 0; temp[i] != '\0'; i++) {
        buf[index++] = temp[i];
    }

    buf[index++] = 'H';
    buf[index] = '\0';

    output_string(buf);
}

void render_game_entities(volatile board_t *game_board, volatile ship_t ship) {
    // Draw all active bullets
    for (uint8_t i = 0; i < MAX_NUM_BULLETS; i++) {
        if (game_board->bullets[i].in_frame) {
            bullet_draw(game_board->bullets[i].y, game_board->bullets[i].x);
        }
    }

    // Draw all active asteroids
    for (uint8_t i = 0; i < MAX_NUM_ASTEROIDS; i++) {
        if (game_board->asteroids[i].in_frame) {
            asteroid_draw(game_board->asteroids[i].y,
                          game_board->asteroids[i].x);
        }
    }

    // Draw and decay collision markers, compact array
    for (uint8_t i = 0; i < game_board->collision_count; i++) {
        collision_draw(game_board->collisions[i].y,
                       game_board->collisions[i].x);
    }
    game_board->collision_count = 0; // clear all after drawing

    // Draw ship
    ship_draw(ship.y, ship.x);
}
