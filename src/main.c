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
#include "uart.h"

#define UART_RXIC (1 << 4)

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
    // uart_interrupt_init();

    start_game();

    while (1) {
        if (timer_ticked) { // interrupt happening here, thread safety
            // timer =  0

            // user input
            uint8_t data = uart_read_blocking();
            UART0->ICR = UART_RXIC; // read first and then clear

            switch (data) {
            case LEFT:
                ship_move_left(&ship);
                break;
            case RIGHT:
                ship_move_right(&ship);
                break;
            case SPACE:
                bullet_spawn(&game_board, ship.y - SHIP_HEIGHT, ship.x);
                break;
            default:
                break;
            }
            // user pressed key to move ship
            // logic
            //rendering

            timer_ticked = false;

            __disable_irq();
           
            bullet_move_all_up(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            asteroid_move_all_down(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            bool ship_collision = collision_check_with_ship_and_asteroid(ship, &game_board);
            if (!ship_collision){
                render_game_entities(&game_board, ship);
            }

            // Update counts based on actual active entities
            game_board.bullet_count = count_active_bullets(&game_board);
            game_board.asteroid_count = count_active_asteroids(&game_board);

            __enable_irq();

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
                while (response != 'y') {
                    response = uart_read_blocking();
                }
                timer_start();
                start_game();
            }
        }
        // timer = ?
    }
}
