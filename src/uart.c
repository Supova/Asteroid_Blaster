#include "TM4C123.h" // device headers
#include "uart.h"
#include "config.h"
#include "utils.h"

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

/* Wait (block) until a character arrives on the serial port, then return it */
uint8_t uart_read_blocking(void) {
    while (UART0->FR & (1 << 4)); // busy wait while RX FIFO is empty
    return (uint8_t)(UART0->DR & 0xFF); // read from data reg and return 8 bit or recieved char
}

void uart_interrupt_init(void) {
    UART0->ICR = (1 << 4); // Clear any pending/stale RX interrupt before enabling
    UART0->IM = (1 << 4); // Generate an interrupt when data arrives in RX FIFO
    NVIC_EnableIRQ(UART0_IRQn); // Enable UART0 interrupts in the ARM CPU
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