// set compiler include path to have "include"
#include "TM4C123.h"
#include "asteroid.h"
#include "config.h"
#include "game.h"
#include "render.h"
#include "timer.h"
#include "uart.h"
#include "utils.h"
#include "bullet.h"
#include "collision.h"
#include "ship.h"

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

    __enable_irq(); // put this in handlers instead
    start_game();

    while (1) {
        if (timer_ticked) {
            timer_ticked = false;
            bullet_move_all_up(&game_board); 
            delay(100000);
            asteroid_move_all_down(&game_board);
            delay(100000);
            collision_check_with_bullet_and_asteroid(&game_board);
            collision_check_with_ship_and_asteroid(ship, &game_board);
            
        }
    }
}
