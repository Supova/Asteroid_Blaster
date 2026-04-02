#include "asteroid.h"
#include "bullet.h"
#include "collision.h"
#include "config.h"
#include "critical_section.h"
#include "game.h"
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
    uart_interrupt_init();

    start_game();

    while (1) {
        if (timer_ticked) {
            timer_ticked = false;

            hal_critical_enter();

            bullet_move_all_up(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            asteroid_move_all_down(&game_board);
            collision_check_with_bullet_and_asteroid(&game_board);

            bool ship_collision =
                collision_check_with_ship_and_asteroid(ship, &game_board);

            if (!ship_collision) {
                render_game_entities(&game_board, ship);
            }

            // Update counts based on actual active entities
            game_board.bullet_count = count_active_bullets(&game_board);
            game_board.asteroid_count = count_active_asteroids(&game_board);

            hal_critical_exit();

            if (game_board.asteroid_count == 0 && !game_over_flag) {
                game_over_flag = true;
            }

            if (game_over_flag) {
                game_over_flag = false;
                game_over();

                output_character(CLEAR_SCREEN);
                output_string(prompt_game_beginning);
                response = ' ';
                while (response != 'y') {
                    response = uart_read_blocking();
                }

                timer0_period_ticks /= 2;
                timer_change_speed(timer0_period_ticks);

                start_game();
            }
        }
    }
}
