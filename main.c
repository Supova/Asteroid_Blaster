#include "asteroid.h"
#include "bullet.h"
#include "collision.h"
#include "config.h"
#include "critical_section.h"
#include "game.h"
#include "input.h"
#include "render.h"
#include "ship.h"
#include "timer.h"
#include "uart.h"
#include "uart_hal.h"
#include "utils.h"

int main(void) {
    uart_init();
    delay(100000);

    output_string(prompt_game_welcome);
    output_string(prompt_game_rules);
    output_string(prompt_game_beginning);

    uint8_t response = ' ';
    while (response != 'y') {
        response = uart_read_blocking();
    }

    timer_init();
    input_init();

    start_game();

    while (1) {
        input_sample();

        if (timer_ticked) {
            timer_ticked = false;

            hal_critical_enter();
            
            GameInput input = input_poll();
            if (input & GAME_INPUT_LEFT)  ship_move_left(&ship);
            if (input & GAME_INPUT_RIGHT) ship_move_right(&ship);
            if (input & GAME_INPUT_SHOOT) bullet_spawn(&game_board, ship.y - SHIP_HEIGHT, ship.x);
            

            bullet_move_all_up(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            asteroid_move_all_down(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            bool ship_hit =
                collision_check_with_ship_and_asteroid(ship, &game_board);

            if (!ship_hit) {
                render_game_entities(&game_board, ship);
            }

            // Update counts based on actual active entities
            game_board.bullet_count = count_active_bullets(&game_board);
            game_board.asteroid_count = count_active_asteroids(&game_board);

            hal_critical_exit();

            if (ship_hit) {
                // Asteroid hit the ship: game over, score resets on restart
                game_over();
            } else if (game_board.asteroid_count == 0) {
                if (hits_this_level > 0) {
                    // Player destroyed at least one asteroid: advance to next level
                    next_level();
                } else {
                    // All asteroids escaped without the player hitting any: game over
                    game_over();
                }
            }
        }
    }
}
