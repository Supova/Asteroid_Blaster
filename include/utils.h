#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdint.h>

#include "TM4C123.h" // device headers
#include "assets.h"

//--------------------MACROS--------------------------------------------------------------------------------------
#define TAB '\t'
#define LINE_FEED '\n'
#define CLEAR_SCREEN '\f'
#define BEGINNING_OF_LINE '\r'

#define BULLET '|'
#define SPACE ' '

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

#define DELETE 0x08 // backspace
#define Y 'Y'

#define GO_UP 0x2
#define GO_DOWN 0x8
#define GO_LEFT 0x4
#define GO_RIGHT 0x1

// Rows and Columns start at 1, not 0
#define ROW_OUT_OF_BOUNDS_LL 1
#define ROW_OUT_OF_BOUNDS_UL 25
#define COL_OUT_OF_BOUNDS_LL 1
#define COL_OUT_OF_BOUNDS_UL 22

#define ROW_IN_BOUNDS_LL 2
#define ROW_IN_BOUNDS_UL 24
#define COL_IN_BOUNDS_LL 2
#define COL_IN_BOUNDS_UL 21

// Escape sequences
const char *last_pos = "\x1B[u";
const char *move_up = "\x1B[1A";
const char *move_down = "\x1B[1B";
const char *move_left = "\x1B[1D";
const char *move_right = "\x1B[1C";
const char *save_pos = "\x1B[s";
const char *clear_display = "\x1B[2J";
const char *initial_pos = "\x1B[11;11H";
const char *hide_cursor = "\x1B[?25l";
const char *show_cursor = "\x1B[?25h";

// Prompts and board
const char *prompt_game_over = "\033[31;1mGAME OVER!\n\r";
const char *prompt_game_beginning =
    "Are you ready to start game? (Press Y)\n\r";
const char *prompt_game_rules =
    "Press 'w' to move up, 'a' to move left, 's' to move down, and 'd' to move "
    "right.\n\r Press SW1 to increase movement speed. \n\r If cursor '*' "
    "collides with a wall game ends.\n\r";

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

// Globals
volatile struct board game_board;

// Function Declarations -----------------------------------------------------------------------
void uart_interrupt_init(void);
uint8_t uart_read_blocking(void);
void uart_init(void);
void UART0_Handler(void);
void output_character(char c);
void output_string(const char* str);
uint8_t simple_read_character(void);

void cursor_goto(uint32_t row, uint32_t col);
void int2string(uint32_t number, char* string);
uint32_t string2int(char* string);


// Function definitions -----------------------------------------------------------------------
void uart_interrupt_init(void) {
    UART0->ICR = (1 << 4);
    UART0->IM = (1 << 4);
    NVIC_EnableIRQ(UART0_IRQn);
}

uint8_t uart_read_blocking(void) {
    while (UART0->FR & (1 << 4)) {
    }
    return (uint8_t)(UART0->DR & 0xFF);
}

void uart_init(void) {
    SYSCTL->RCGCUART |= (1 << 0);
    SYSCTL->RCGCGPIO |= (1 << 0);
    GPIOA->AFSEL |= (1 << 0) | (1 << 1);
    GPIOA->PCTL &= ~0x000000FF;
    GPIOA->PCTL |= 0x00000011;
    GPIOA->DEN |= (1 << 0) | (1 << 1);
    UART0->CTL &= ~(1 << 0);
    UART0->IBRD = 104;
    UART0->FBRD = 11;
    UART0->LCRH = (0x3 << 5);
    UART0->CC = 0x0;
    UART0->CTL |= (1 << 0) | (1 << 8) | (1 << 9);
}

void UART0_Handler(void) {
    UART0->ICR = (1 << 4);
    uint8_t data = simple_read_character();
    switch (data) {
    case LEFT:
        // ship movement
        break;
        case RIGHT:
        // ship movement
        break;
    case SPACE:
        // bullet logic
        break;
    default:
        break;
    }
}

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

uint8_t simple_read_character(void) { 
    return (uint8_t)(UART0->DR & 0xFF); 
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

#endif
