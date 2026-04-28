#include "gpio.h"
#include "TM4C123.h"
#include "utils.h"
#include "game.h"
#include <stdint.h>

void blink_red_LED(void) {
    SYSCTL->RCGCGPIO |= PORTF;
    GPIOF->DIR |= RED_LED;
    GPIOF->DEN |= RED_LED;

    uint8_t blink_count = 6;
    while (blink_count--) {
        GPIOF->DATA ^= RED_LED;
        delay(900000);
    }
}

