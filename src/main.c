// set compiler include path to have "include"
#include "config.h"
#include "render.h"
#include "uart.h"
#include "utils.h"
#include "game.h"

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

    uart_interrupt_init();
    start_game();

    while (1) {
    }
}
