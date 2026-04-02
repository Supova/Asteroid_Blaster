#include "render.h"
#include "uart_hal.h"
#include "asteroid.h"
#include "bullet.h"
#include "collision.h"
#include "config.h"
#include "ship.h"

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
