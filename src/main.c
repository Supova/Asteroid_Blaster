// set compiler include path to have "include"
#include "config.h"
#include "utils.h"
#include "uart.h"
#include "render.h"

int main() {
    uart_init();

    output_string(prompt_game_beginning);
    output_string(prompt_game_rules);

    while (1) {
    }
}
