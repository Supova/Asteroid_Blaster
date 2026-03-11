#ifndef TIMER_H
#define TIMER_H

extern volatile bool timer_ticked;

void timer_init(void);
void TIMER0A_Handler(void);

#endif