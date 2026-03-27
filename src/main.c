// set compiler include path to have "include"
#include "TM4C123.h"
#include "asteroid.h"
#include "bullet.h"
#include "collision.h"
#include "config.h"
#include "game.h"
#include "render.h"
#include "ship.h"
#include "timer.h"
#include "uart.h"
#include "utils.h"

int main() {
    uart_init();
    delay(100000);

    output_string(prompt_game_welcome);
    output_string(prompt_game_rules);
    output_string(prompt_game_beginning);

    char response = ' ';
    while (response != 'y') {
        response = uart_read_blocking();
    }

    timer_init();
    uart_interrupt_init();

    start_game();

    while (1) {
        if (timer_ticked) { // interrupt happening here, thread safety
            timer_ticked = false;

            __disable_irq();

            // ! test
            uint8_t index = game_board.collision_count;
            for (int k = 0; k < index; k++) {
                collision_erase(game_board.collisions[k].y, game_board.collisions[k].x);
                game_board.collisions[game_board.collision_count].x = 0;
                game_board.collisions[game_board.collision_count].y = 0;
                game_board.collision_count--;
            }
           
            bullet_move_all_up(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            asteroid_move_all_down(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            bool ship_collision = collision_check_with_ship_and_asteroid(ship, &game_board);
            if (!ship_collision){
                render_game_entities(&game_board, ship);
            }
            __enable_irq();

            // Update counts based on actual active entities
            game_board.bullet_count = count_active_bullets(&game_board);
            game_board.asteroid_count = count_active_asteroids(&game_board);


            if (game_board.asteroid_count == 0 && !game_over_flag) {
                game_over_flag = true;
                game_over();
            }
            // game over --> time stops

           if (game_over_flag) {
                // restart game
                game_over_flag = false;
                output_character(CLEAR_SCREEN);
                output_string(prompt_game_beginning);
                response = ' ';
                __disable_irq();
                while (response != 'y') {
                    response = uart_read_blocking(); // blocking = polling
                }
                 __enable_irq();
                timer_start();
                start_game();
            }
        }
    }
}
