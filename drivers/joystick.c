#include "joystick.h"
#include "adc.h"
#include "TM4C123.h"

/* Deadzone radius around the calibrated center (12-bit ADC units).
 * Increase if the ship drifts at rest; decrease for more sensitivity. */
#define DEADZONE  500

/* SW on PF4 — locked pin, needs unlock sequence */
#define PORTF_EN       (1 << 5)
#define SW_PIN         (1 << 4)
#define GPIO_LOCK_KEY  0x4C4F434B

/* Calibrated resting center — set once in joystick_init() */
static uint32_t center_x = 2047;
static uint32_t center_y = 2047;

void joystick_init(void) {
    adc_init();

    /* Enable Port F clock and wait for ready */
    SYSCTL->RCGCGPIO |= PORTF_EN;
    while (!(SYSCTL->PRGPIO & PORTF_EN))
        ;

    /* PF4 is a locked pin — must unlock before configuring */
    GPIOF->LOCK = GPIO_LOCK_KEY;
    GPIOF->CR  |= SW_PIN;

    /* Configure PF4 as digital input with internal pull-up */
    GPIOF->DIR   &= ~SW_PIN;
    GPIOF->PUR   |=  SW_PIN;
    GPIOF->DEN   |=  SW_PIN;
    GPIOF->AMSEL &= ~SW_PIN;

    /* Calibrate: average 8 reads at rest to find the true center */
    uint32_t sum_x = 0, sum_y = 0;
    uint32_t x, y;
    for (int i = 0; i < 8; i++) {
        adc_read(&x, &y);
        sum_x += x;
        sum_y += y;
    }
    center_x = sum_x / 8;
    center_y = sum_y / 8;
}

JoyDir joystick_get_dir(void) {
    uint32_t vrx, vry;
    adc_read(&vrx, &vry);

    /* Y axis is intentionally ignored — any tilt with a left/right
     * component counts as left/right regardless of vertical position. */
    (void)vry;

    if      (vrx > center_x + DEADZONE) return JOY_LEFT;
    else if (vrx < center_x - DEADZONE) return JOY_RIGHT;
    else                                return JOY_CENTER;
}

/* SW is active low (pull-up): pin reads 0 when pressed */
uint8_t joystick_sw_pressed(void) {
    return !(GPIOF->DATA & SW_PIN);
}
