#include "TM4C123.h" // Device header
#include "utils.h"  // set compiler include path to have "include"

int main() {
    uart_init();

    output_string(prompt_game_beginning);
    output_string(prompt_game_rules);

    while (1) {
    }
}
