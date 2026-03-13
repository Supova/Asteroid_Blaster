#include "timer.h"
#include "TM4C123.h"
#include "config.h"
#include <stdbool.h>

volatile bool timer_ticked = false;

void timer_init(void) {
    SYSCTL->RCGCTIMER |= (1 << 0);
    TIMER0->CTL &= ~(1 << 0);
    TIMER0->CFG = 0x0;
    TIMER0->TAMR = 0x2;
    TIMER0->TAILR = STARTING_SPEED;
    TIMER0->ICR = (1 << 0);
    TIMER0->IMR |= (1 << 0);
    NVIC_EnableIRQ(TIMER0A_IRQn);
    TIMER0->CTL |= (1 << 0);
}

void timer_stop(void) {
    timer_ticked = false;
    TIMER0->CTL &= ~(1 << 0);
}

void TIMER0A_Handler(void) {
    // clear the interrupt
    TIMER0->ICR = (1 << 0);
    timer_ticked = true;
}