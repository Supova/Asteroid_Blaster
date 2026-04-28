#include "utils.h"
#include "assets.h"
#include <stdint.h>

void delay(volatile uint32_t seconds) {
    for (volatile uint32_t i = 0; i < seconds; i++)
        ;
}

void int2string(uint8_t number, char *string) {

    if (number == 0) {
        string[0] = '0';
        string[1] = '\0';
        return;
    }

    uint8_t index = 0;
    while (number) {
        uint8_t digit = number % 10;
        string[index++] = '0' + digit;
        number /= 10;
    }
    string[index] = '\0';

    uint8_t left = 0;
    uint8_t right = index - 1;
    while (left < right) {
        uint8_t temp = string[right];
        string[right] = string[left];
        string[left] = temp;
        left++;
        right--;
    }
}

uint8_t count_active_asteroids(volatile board_t *game_board) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < MAX_NUM_ASTEROIDS; i++) {
        if (game_board->asteroids[i].in_frame) {
            count++;
        }
    }
    return count;
}
