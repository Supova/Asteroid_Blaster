#include "utils.h"
#include "TM4C123.h"
#include "assets.h"
#include <stdint.h>

void delay(volatile uint32_t seconds) {
    for (volatile uint32_t i = 0; i < seconds; i++)
        ;
}

uint8_t simple_read_character(void) { return (uint8_t)(UART0->DR & 0xFF); }

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

uint32_t get_random_seed(void) {
    return TIMER0->TAR; // Use current timer value as seed
}

uint8_t count_active_bullets(volatile board_t *game_board) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < MAX_NUM_BULLETS; i++) {
        if (game_board->bullets[i].in_frame) {
            count++;
        }
    }
    return count;
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
