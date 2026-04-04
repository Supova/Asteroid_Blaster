#include "config.h"

#ifdef INPUT_MODE_UART

#include "input.h"
#include "uart.h"
#include "ship.h"
#include "bullet.h"
#include "game.h"
#include "config.h"

/*
 * UART keyboard input implementation.
 *
 * Ship movement and shooting happen immediately inside UART0_Handler,
 * exactly as before the input abstraction was introduced. This preserves
 * responsive control — the ship moves the instant a key is received,
 * not on the next 1 Hz game tick.
 *
 * input_poll() always returns NONE in this mode. The main loop's input
 * block becomes a no-op, but the code stays mode-agnostic.
 */

/* Called from UART0_Handler in drivers/uart.c */
void input_uart_on_key(uint8_t key) {
    switch (key) {
        case LEFT:  ship_move_left(&ship);                                  break;
        case RIGHT: ship_move_right(&ship);                                 break;
        case SPACE: bullet_spawn(&game_board, ship.y - SHIP_HEIGHT, ship.x); break;
        default:    break;
    }
}

void input_init(void) {
    uart_interrupt_init();
}

void input_sample(void) {
    /* no-op: UART ISR handles everything immediately */
}

GameInput input_poll(void) {
    return GAME_INPUT_NONE; /* all actions handled immediately in ISR */
}

#endif /* INPUT_MODE_UART */
