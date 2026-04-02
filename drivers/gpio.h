#ifndef GPIO_H
#define GPIO_H

#define PORTF (1u << 5)
#define RED_LED (1u << 1)
#define SW1 (1u << 4)

void blink_red_LED(void);
void gpio_interrupt_init(void);
void GPIOF_Handler(void);

#endif /* GPIO_H */