#include "asteroid.h"
#include "assets.h"
#include "collision.h"
#include "config.h"
#include "game.h"
#include "render.h"
#include "utils.h"


void asteroid_draw(uint32_t y, uint32_t x) {
    cursor_goto(y, x);
    output_string(ASTEROID_SYMBOL);
}

void asteroid_erase(uint32_t y, uint32_t x) {
    cursor_goto(y, x);
    output_string(BLANK);
}

void asteroid_move_down(volatile asteroid_t *asteroid) {
    asteroid_out_of_bounds_check(asteroid);

    if (asteroid->y < PLAYABLE_MAX_Y) {
        asteroid_erase(asteroid->y, asteroid->x);
        asteroid->y++;
    }
}

void asteroid_move_all_down(volatile board_t *game_board) {
    for (int i = 0; i < MAX_NUM_ASTEROIDS; i++) {
        if (game_board->asteroids[i].in_frame) {
            volatile asteroid_t *asteroid = &(game_board->asteroids[i]);
            asteroid_move_down(asteroid);
        }
    }
}

position_t asteroid_position_randomize() {
    position_t pos;
    uint32_t seed = get_random_seed();

    // Random column: 2-21  [formula: rand() % (max - min + 1) + min]
    pos.x = (seed % (PLAYABLE_MAX_X - PLAYABLE_MIN_X + 1)) + PLAYABLE_MIN_X;

    // Random row: 2-8 (leave space for ship at bottom)
    // seed rightshifted to decorrelate coordinates
    pos.y = ((seed >> 8) % ((PLAYABLE_MAX_Y / 2) - PLAYABLE_MIN_Y - 3)) + PLAYABLE_MIN_Y;

    return pos;
}

bool position_taken(position_t pos, volatile board_t *game_board) {
    for (int i = 0; i < MAX_NUM_ASTEROIDS; i++) { 
        if (game_board->asteroids[i].in_frame &&
            game_board->asteroids[i].x == pos.x &&
            game_board->asteroids[i].y == pos.y) {
            return true;
        }
    }
    return false;
}


void asteroids_create(volatile board_t *game_board) {
    game_board->asteroid_count = MAX_NUM_ASTEROIDS;

    // place random asteroids, ensuring no duplicates
    uint8_t asteroids_placed = 0;
    while (asteroids_placed < MAX_NUM_ASTEROIDS) {
        position_t new_pos = asteroid_position_randomize();

        if (!position_taken(new_pos, game_board)) {
            game_board->asteroids[asteroids_placed].x = new_pos.x;
            game_board->asteroids[asteroids_placed].y = new_pos.y;
            // game_board->asteroids[asteroids_placed].in_frame = false; 
            game_board->asteroids[asteroids_placed].in_frame = true; // make last 2/3 inactive
            asteroids_placed++;
        }
    }
}

void asteroid_out_of_bounds_check(volatile asteroid_t *asteroid) {
    if (asteroid->y == PLAYABLE_MAX_Y) {
        asteroid_erase(asteroid->y, asteroid->x);
        asteroid->in_frame = false;
    }
}


/*
new levels: if asteroids go out of bounds without being hit, 
    there is penalty
increase speed for next levels


*/


