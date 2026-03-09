// set compiler include path to have "include"
#include "config.h"
#include "render.h"
#include "uart.h"
#include "utils.h"

int main() {
    uart_init();

    output_string(prompt_game_welcome);
    output_string(prompt_game_rules);
    output_string(prompt_game_beginning);

    // wait for user to start game
    char response = ' ';
    while (response != 'y') {
        response = uart_read_blocking();
    }

    uart_interrupt_init();
    while (1) {
    }
}
