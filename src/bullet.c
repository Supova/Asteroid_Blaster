#include "bullet.h"
#include "config.h"
#include "render.h"

void bullet_draw(uint32_t y, uint32_t x) {
    cursor_goto(y, x);
    output_string(BULLET_SYMBOL);
}

void bullet_erase(uint32_t y, uint32_t x) {
    cursor_goto(y, x);
    output_string(BLANK);
}

// * TODO: refactor for faster algo
void bullet_spawn(volatile board_t *board, uint8_t y, uint8_t x) {
    for (int i = 0; i < MAX_NUM_BULLETS; i++) {
        if (!board->bullets[i].in_frame) {
            board->bullets[i].id       = board->bullet_count++;  // increment here
            board->bullets[i].x        = x;
            board->bullets[i].y        = y;
            board->bullets[i].in_frame = true;  // mark as active
            bullet_draw(y, x);
            return;
        }
    }
}


void bullet_move_up(volatile bullet_t *bullet) {
    bullet_out_of_bounds_check(bullet);
    if (bullet->y > PLAYABLE_MIN_Y) {
        bullet_erase(bullet->y, bullet->x);
        bullet->y--;
    }
}

void bullet_move_all_up(volatile board_t *game_board) {
    for (int i = 0; i < MAX_NUM_BULLETS; i++) {
        if (game_board->bullets[i].in_frame == true) {
            volatile bullet_t *bullet = &(game_board->bullets[i]);
            bullet_move_up(bullet);
        }
    }
}

void bullet_out_of_bounds_check(volatile bullet_t *bullet){
    if (bullet->y == PLAYABLE_MIN_Y) {
        bullet_erase(bullet->y, bullet->x);
        bullet->in_frame = false;
    }
}
