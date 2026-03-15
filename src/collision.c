#include "collision.h"
#include "assets.h"
#include "config.h"
#include "game.h"
#include "render.h"

void collision_draw(uint32_t y, uint32_t x) {
    cursor_goto(y, x);
    output_string(COLLISION_SYMBOL);
}

bool collision_check_with_ship_and_asteroid(ship_t ship, asteroid_t asteroid){
    // check calculated positions and if they equal
    return true;
}


void collision_check_with_bullet_and_asteroid(board_t* game_board, asteroid_t *asteroid){
    for (int i = 0; i < MAX_NUM_BULLETS; i++) {
            if (asteroid->x == game_board->bullets[i].x && 
                asteroid->y == game_board->bullets[i].y){
                collision_draw(asteroid->y, asteroid->x);
								asteroid->in_frame = false; 
								game_board->bullets[i].in_frame = false; 
                score++;
                game_over();
                return;
        }
    }
}