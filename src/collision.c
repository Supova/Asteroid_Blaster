#include "collision.h"
#include "assets.h"
#include "asteroid.h"
#include "bullet.h"
#include "config.h"
#include "game.h"
#include "render.h"

void collision_draw(uint32_t y, uint32_t x) {
    cursor_goto(y, x);
    output_string(COLLISION_SYMBOL);
}

<<<<<<< Updated upstream
void collision_check_with_ship_and_asteroid(volatile ship_t ship,
=======
void collision_erase(uint32_t y, uint32_t x) {
    cursor_goto(y, x);
    output_string(BLANK);
}


bool collision_check_with_ship_and_asteroid(volatile ship_t ship,
>>>>>>> Stashed changes
                                            volatile board_t *game_board) {
    for (int i = 0; i < MAX_NUM_ASTEROIDS; i++) {
        if (game_board->asteroids[i].in_frame &&
            game_board->asteroids[i].x == ship.x &&
            game_board->asteroids[i].y == ship.y) {
<<<<<<< Updated upstream
            collision_draw(game_board->asteroids[i].y,
                           game_board->asteroids[i].x);
            game_over();
=======
            game_over_flag = true;
            return true;
>>>>>>> Stashed changes
        }
    }
}

void collision_check_with_bullet_and_asteroid(volatile board_t *game_board) {
    for (int i = 0; i < MAX_NUM_BULLETS; i++) {
        for (int j = 0; j < MAX_NUM_ASTEROIDS; j++) {
            if (game_board->bullets[i].in_frame &&
                game_board->asteroids[j].in_frame &&
                game_board->asteroids[j].x == game_board->bullets[i].x &&
                game_board->asteroids[j].y == game_board->bullets[i].y) {

<<<<<<< Updated upstream
=======
                // Store collision location for rendering
                // ! test
                // if (game_board->collision_count < MAX_NUM_ASTEROIDS) {
                    game_board->collisions[game_board->collision_count].x = game_board->asteroids[j].x;
                    game_board->collisions[game_board->collision_count].y = game_board->asteroids[j].y;
                    game_board->collision_count++;
                // }

>>>>>>> Stashed changes
                game_board->asteroids[j].in_frame = false;
                asteroid_erase(game_board->asteroids[j].y,
                               game_board->asteroids[j].x);

                game_board->bullets[i].in_frame = false;
                bullet_erase(game_board->bullets[i].y,
                             game_board->bullets[i].x);

                collision_draw(game_board->asteroids[j].y,
                               game_board->asteroids[j].x);
                score++;
								game_board->asteroid_count--;  
								game_board->bullet_count--;

            }
        }
    }
}