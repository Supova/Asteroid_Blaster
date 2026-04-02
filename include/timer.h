#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include <stdint.h>

extern volatile bool timer_ticked;
extern volatile uint32_t timer0_period_ticks;
void timer_init(void);
void timer_stop(void);
void timer_change_speed(uint32_t timer0_period_ticks);
void TIMER0A_Handler(void);

#endif /* TIMER_H */