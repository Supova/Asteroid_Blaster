#include "uart.h"
#include "TM4C123.h" // device headers
#include "config.h"
#include "utils.h"
#include "ship.h"
#include "assets.h"
#include "bullet.h"
#include "game.h"

void uart_init(void) {
    /* Enable clocks for UART0 and GPIO Port A */
    SYSCTL->RCGCUART |= (1 << 0);
    SYSCTL->RCGCGPIO |= (1 << 0);

    /* Configure PA0 (RX) and PA1 (TX) for UART alternate function */
    GPIOA->AFSEL |= (1 << 0) | (1 << 1);
    GPIOA->PCTL &= ~0x000000FF;
    GPIOA->PCTL |= 0x00000011;
    GPIOA->DEN |= (1 << 0) | (1 << 1);

    /* Configure UART0 */
    UART0->CTL &= ~(1 << 0);
    UART0->IBRD = 104;
    UART0->FBRD = 11;
    UART0->LCRH = (0x3 << 5);
    UART0->CC = 0x0;
    UART0->CTL |= (1 << 0) | (1 << 8) | (1 << 9);
}

uint8_t uart_read_blocking(void) {
    /* Block until data available in RX FIFO */
    while (UART0->FR & (1 << 4))
        ;
    return (uint8_t)(UART0->DR & 0xFF);
}

void uart_interrupt_init(void) {
    UART0->ICR = (1 << 4);           // Clear pending RX interrupts
    UART0->IM = (1 << 4);            // Enable RX interrupt generation
    NVIC_EnableIRQ(UART0_IRQn);      // Enable UART0 in CPU interrupt controller
    __enable_irq();                  // Enable global interrupts
}

// * TODO: refactor
void UART0_Handler(void) {
    UART0->ICR = (1 << 4);
    uint8_t data = simple_read_character();
     __disable_irq();
    switch (data) {
    case LEFT:
        ship_move_left(&ship);
        break;
    case RIGHT:
        ship_move_right(&ship);
        break;
    case SPACE:
        bullet_spawn(&game_board, ship.y - SHIP_HEIGHT, ship.x);
        break;
    default:
        break;
    }
    __enable_irq();
}