#include "config.h"

#ifdef INPUT_MODE_JOYSTICK

#include "input.h"
#include "joystick.h"
#include "ship.h"
#include "bullet.h"
#include "game.h"
#include "config.h"

/*
 * Joystick input implementation.
 *
 * input_sample() is called as fast as possible in the main loop.
 * It is rate-limited internally so the ADC is only read at ~20 Hz.
 * Ship movement is applied directly here (same idea as the UART ISR),
 * so the ship responds immediately rather than waiting for the next
 * 1 Hz game tick.
 *
 * The SW button uses edge detection: one shoot event per press,
 * not one per sample while held. The pending flag is consumed by
 * input_poll() on the next game tick.
 *
 * SAMPLE_EVERY controls polling rate. Tune this value if movement
 * feels too fast or too slow — higher = slower polling.
 */

#define SAMPLE_EVERY 80000UL  /* ~20 Hz at 16 MHz system clock */

static uint32_t sample_counter = 0;
static uint8_t  sw_prev        = 0;

void input_uart_on_key(uint8_t key) {
    (void)key; /* joystick mode ignores UART key events */
}

void input_init(void) {
    joystick_init();
}

void input_sample(void) {
    /* SW button is a plain GPIO read — always check it regardless of
     * game speed so shooting is never blocked by the rate limiter. */
    uint8_t sw_now = joystick_sw_pressed();
    if (sw_now && !sw_prev)
        bullet_spawn(&game_board, ship.y - SHIP_HEIGHT, ship.x);
    sw_prev = sw_now;

    /* Direction requires an ADC read — rate-limit to ~20 Hz.
     * At higher game speeds the main loop runs fewer iterations between
     * ticks, so the counter may take longer to reach SAMPLE_EVERY.
     * That's fine: slower ADC polling just means slightly less ship
     * movement per second, which matches the faster game pace. */
    if (++sample_counter < SAMPLE_EVERY) return;
    sample_counter = 0;

    JoyDir dir = joystick_get_dir();
    switch (dir) {
        case JOY_LEFT:  ship_move_left(&ship);  break;
        case JOY_RIGHT: ship_move_right(&ship); break;
        default:        break;
    }
}

GameInput input_poll(void) {
    return GAME_INPUT_NONE; /* all actions handled immediately in input_sample() */
}

#endif /* INPUT_MODE_JOYSTICK */
