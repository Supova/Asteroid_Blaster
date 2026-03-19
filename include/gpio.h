#ifndef GPIO_H
#define GPIO_H

#define PORTF (1 << 5)
#define RED_LED (1 << 1)
#define SW1 (1<<0)

// blink led
void blink_red_LED(void);

// sw1 for restart game
void gpio_interrupt_init(void);
void GPIOF_Handler(void);

#endif