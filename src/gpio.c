#include "gpio.h"
#include "TM4C123.h"
#include "utils.h"
#include "game.h"
#include <stdint.h>

void blink_red_LED(void) {
    SYSCTL->RCGCGPIO |= PORTF;
    GPIOF->DIR |= RED_LED;
    GPIOF->DEN |= RED_LED;

    static uint8_t blink_count = 6;
    while (blink_count--) {
        GPIOF->DATA ^= RED_LED;
        delay(900000);
    }
}

void gpio_interrupt_init(void) {
    SYSCTL->RCGCGPIO |= PORTF;
    GPIOF->DIR &= (~SW1);
    GPIOF->PUR |= SW1;
    GPIOF->DEN |= SW1;

    GPIOF->IS &= (~(1 << 4));
    GPIOF->IBE &= (~(1 << 4));
    GPIOF->IEV &= (~(1 << 4));
    GPIOF->IM |= (1 << 4);
    GPIOF->ICR |= (1 << 4);

    NVIC->ISER[0] |= (1 << 30);
    NVIC->IPR[30] = 0x60;
}

void GPIOF_Handler(void) {
    GPIOF->ICR |= (1 << 4);
    game_over_flag = true;
}