#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

extern volatile bool timer_ticked;

void timer_init(void);
void timer_stop(void);
void TIMER0A_Handler(void);

#endif