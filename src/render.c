#include "TM4C123.h"
#include "render.h"
#include "utils.h"

void output_character(char c) {
    while (UART0->FR & (1 << 5))
        ;
    UART0->DR = c;
}

void output_string(const char *str) {
    while (*str) {
        output_character(*str++);
    }
}

void cursor_goto(uint32_t row, uint32_t col) {
    char buf[12];
    output_character('\x1B');
    output_character('[');
    int2string((uint32_t)row, buf);
    output_string(buf);
    output_character(';');
    int2string((uint32_t)col, buf);
    output_string(buf);
    output_character('H');
}

