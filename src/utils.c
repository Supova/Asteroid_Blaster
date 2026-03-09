#include <stdint.h>
#include "TM4C123.h"
#include "utils.h"
// Globals
volatile struct board game_board;

const char *BOARD = " -------------------- \n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    " -------------------- ";



// Function definitions -----------------------------------------------------------------------

uint8_t simple_read_character(void) { 
    return (uint8_t)(UART0->DR & 0xFF); 
}                  

void int2string(uint32_t number, char *string) {

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

uint32_t string2int(char *string) {
    uint32_t index = 0;
    uint32_t total = 0;
    while (string[index] != '\0') {
        uint32_t digit = string[index] - '0';
        total = (total * 10) + digit;
        index++;
    }
    return total;
}