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
           
            bullet_move_all_up(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            asteroid_move_all_down(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            collision_check_with_ship_and_asteroid(ship, &game_board);
            render_game_entities(&game_board, ship);

            __enable_irq();

            if (game_board.asteroid_count == 0 && !game_over_flag) {
                game_over_flag = true;
                game_over();
            }
            // game over --> time stops

           if (game_over_flag) {
                // restart game
                game_over_flag = false;
                output_string(prompt_game_beginning);
                response = ' ';
                while (response != 'y') {
                    response = uart_read_blocking();
                }
                timer_start();
                start_game();
            }
        }
    }
}
