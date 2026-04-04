#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

/*
 * Hardware-agnostic input interface.
 *
 * The game loop calls input_poll() once per tick and acts on
 * the returned bitmask — it never knows whether input came from
 * a UART keyboard or a joystick.
 *
 * Two implementations exist:
 *   hal/input_uart.c     — keyboard via UART interrupt (Stage 1)
 *   hal/input_joystick.c — KY-023 ADC + SW button (Stage 2)
 *
 * Only one implementation is compiled at a time, selected by
 * defining INPUT_MODE_UART or INPUT_MODE_JOYSTICK in config.h.
 */

typedef enum {
    GAME_INPUT_NONE  = 0,
    GAME_INPUT_LEFT  = (1 << 0),
    GAME_INPUT_RIGHT = (1 << 1),
    GAME_INPUT_SHOOT = (1 << 2),
} GameInput;

/* Call once at startup (before enabling interrupts / timer) */
void      input_init(void);

/*
 * Call as fast as possible in the main loop (outside the game tick).
 * UART mode: no-op — the ISR already handles everything immediately.
 * Joystick mode: rate-limited ADC poll; applies ship movement directly
 *                and edge-detects the SW button for shoot.
 */
void      input_sample(void);

/*
 * Called from UART0_Handler to forward a raw key byte.
 * Only used by input_uart.c — ignored in joystick mode.
 * Declared here so drivers/uart.c can call it without
 * pulling in game-layer headers.
 */
void input_uart_on_key(uint8_t key);

/*
 * Call once per game tick.
 * Returns a bitmask of all inputs active at that moment.
 * For UART: consumes the pending key event and clears it.
 * For joystick: samples the ADC and SW pin directly.
 */
GameInput input_poll(void);

#endif /* INPUT_H */
