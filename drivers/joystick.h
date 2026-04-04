#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>

/*
 * KY-023 joystick driver
 *   VRx -> PE3 (AIN0)
 *   VRy -> PE2 (AIN1)
 *   SW  -> PF4
 *
 * Sits on top of adc.c for the analog axes.
 * SW is polled (active low, internal pull-up).
 */

typedef enum {
    JOY_CENTER,
    JOY_LEFT,
    JOY_RIGHT,
    JOY_UP,
    JOY_DOWN,
    JOY_UP_LEFT,
    JOY_UP_RIGHT,
    JOY_DOWN_LEFT,
    JOY_DOWN_RIGHT
} JoyDir;

void   joystick_init(void);
JoyDir joystick_get_dir(void);
uint8_t joystick_sw_pressed(void);  /* returns 1 if button is held down */

#endif /* JOYSTICK_H */
