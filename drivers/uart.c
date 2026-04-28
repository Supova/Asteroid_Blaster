#include "uart.h"
#include "TM4C123.h"
#include "config.h"
#include "bullet.h"
#include "game.h"
#include "ship.h"
/* UART0 clock, GPIO clock */
#define UART0_EN (1 << 0)
#define GPIOA_EN (1 << 0)

/* UART0 control bits */
#define UART_CTL_UARTEN (1 << 0)
#define UART_CTL_TXE (1 << 8)
#define UART_CTL_RXE (1 << 9)

/* UART0 line control */
#define UART_LCRH_WLEN_8 (0x3 << 5) // High byte, Word Length = 8-bit

/* GPIO alternate function & digital enable */
#define PA0_RX (1 << 0)
#define PA1_TX (1 << 1)
#define PA_AF_UART 0x1

#define UART_RX_FIFO_EMPTY (1 << 4)
#define UART_RXIM (1 << 4)
#define UART_RXIC (1 << 4)

static uint8_t uart_fifo_read_char(void) { return (uint8_t)(UART0->DR & 0xFF); }

void uart_init(void) {
    /* Enable clocks for UART0 and GPIO Port A, wait until ready */
    SYSCTL->RCGCUART |= UART0_EN;
    SYSCTL->RCGCGPIO |= GPIOA_EN;
    while (!(SYSCTL->PRUART & UART0_EN))
        ;
    while (!(SYSCTL->PRGPIO & GPIOA_EN))
        ;

    /* Configure PA0 (RX) and PA1 (TX) for UART alternate function */
    GPIOA->AFSEL |= PA0_RX | PA1_TX;
    GPIOA->PCTL &= ~0x000000FF;
    GPIOA->PCTL |= 0x00000011;
    GPIOA->DEN |= PA0_RX | PA1_TX;

    /* Configure UART0: 9600 baud rate */
    UART0->CTL &= ~UART_CTL_UARTEN;  // disable UART before config
    UART0->IBRD = 104;  // integer baud rate divisor
    UART0->FBRD = 11;   // fractional baud rate divisor
    UART0->LCRH = UART_LCRH_WLEN_8;  // 8-bit, no parity, 1 stop bit
    UART0->CC = 0x0;  // use system clock
    UART0->CTL |= UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;  // enable UART + TX/RX
}

uint8_t uart_read_blocking(void) {
    /* Block until data available in RX FIFO */
    while (UART0->FR & UART_RX_FIFO_EMPTY)
        ;
    return (uint8_t)(UART0->DR & 0xFF);
}

void uart_interrupt_init(void) {
    UART0->ICR = UART_RXIC;      // Clear pending RX interrupts
    UART0->IM = UART_RXIM;       // Enable RX interrupt generation
    NVIC_EnableIRQ(UART0_IRQn); // Enable UART0 in CPU interrupt controller
}

void uart_interrupt_disable(void) {
    NVIC_DisableIRQ(UART0_IRQn);
    UART0->IM &= ~UART_RXIM;
}

void UART0_Handler(void) {
    uint8_t data = uart_fifo_read_char();
    UART0->ICR = UART_RXIC;
    switch (data) {
        case LEFT:  ship_move_left(&ship);                                   break;
        case RIGHT: ship_move_right(&ship);                                  break;
        case SPACE: bullet_spawn(&game_board, ship.y - SHIP_HEIGHT, ship.x); break;
        default:    break;
    }
}
