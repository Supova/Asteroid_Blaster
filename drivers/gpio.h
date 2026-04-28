#ifndef GPIO_H
#define GPIO_H

#define PORTF (1u << 5)
#define RED_LED (1u << 1)

void blink_red_LED(void);

#endif /* GPIO_H */