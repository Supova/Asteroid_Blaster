#include "uart_hal.h"
#include "utils.h"
#include "TM4C123.h"

void output_character(char c) {
    while (UART0->FR & (1 << 5))
        ;          // WAIT (block) while TX FIFO is full
    UART0->DR = c; // Write char when FIFO has space
}

void output_string(const char *str) {
    while (*str) {
        output_character(*str++);
    }
}

void cursor_goto(uint32_t y, uint32_t x) {
    char buf[20];
    uint8_t index = 0;

    buf[index++] = '\x1B';
    buf[index++] = '[';

    // Append Y coordinate
    char temp[12];
    int2string(y, temp);
    for (uint8_t i = 0; temp[i] != '\0'; i++) {
        buf[index++] = temp[i];
    }

    buf[index++] = ';';

    // Append X coordinate
    int2string(x, temp);
    for (uint8_t i = 0; temp[i] != '\0'; i++) {
        buf[index++] = temp[i];
    }

    buf[index++] = 'H';
    buf[index] = '\0';

    output_string(buf);
}
