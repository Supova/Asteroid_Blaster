#include "TM4C123.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>

#define TimerA_EN (1<<0)
#define TIMER_CFG_MODE_32BIT (0x0)
#define TIMER_TAMR_PERIODIC (0x2)
// #define TIMER0A_PERIOD_TICKS (16000000) // 16M
#define TIMERA_TIME_OUT_INT_MASK (1 << 0)
#define TIMERA_TIME_OUT_FLAG (1 << 0)

volatile uint32_t timer0_period_ticks = 16000000;
volatile bool timer_ticked = false;

void timer_init(void) {
    volatile uint32_t dummy_for_delay; // need volatile so it's not optimized away
    SYSCTL->RCGCTIMER |= (1 << 0);
    dummy_for_delay = SYSCTL->RCGCTIMER; // delay for timer to finish activating
    TIMER0->CTL &= ~TimerA_EN; 
    TIMER0->CFG = TIMER_CFG_MODE_32BIT;
    TIMER0->TAMR = TIMER_TAMR_PERIODIC; // count down (default)
    TIMER0->TAILR = timer0_period_ticks;  // reload value - rate of interruption - 16 MHz; fires every period = timer count/clock fq
    TIMER0->IMR |= TIMERA_TIME_OUT_INT_MASK; // timeout is going to cause interrupt
    TIMER0->ICR |= TIMERA_TIME_OUT_FLAG; // clear timeout flag by setting bit(so interrupt can occur after setup)
    NVIC_EnableIRQ(TIMER0A_IRQn);
    TIMER0->CTL |= TimerA_EN; 
}

void timer_stop(void) {
    timer_ticked = false;
    TIMER0->CTL &= ~TimerA_EN;
}

void timer_change_speed(uint32_t timer0_period_ticks){
    if (timer0_period_ticks <= 0x00000050){
        return;
    }
    TIMER0->CTL &= ~TimerA_EN; 
    TIMER0->TAILR = timer0_period_ticks;
    TIMER0->CTL |= TimerA_EN; 
}

uint32_t timer_get_count(void) {
    return TIMER0->TAR;
}

void TIMER0A_Handler(void) {
    // acknowledge and clear the interrupt
    TIMER0->ICR |= TIMERA_TIME_OUT_FLAG;
    timer_ticked = true;
}
