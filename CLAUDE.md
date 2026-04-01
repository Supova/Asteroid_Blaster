# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is an embedded systems project: a terminal-based asteroid blaster game for the TM4C123GH6PM microcontroller (TivaC). The game runs on bare-metal firmware (no OS) and uses UART for terminal I/O and timer interrupts for game loop timing.

**Project Stages:**
- Stage 1 (Current): Terminal-based game via UART
- Stage 2 (Planned): Hardware-based game with LCD and buttons
- Stage 3 (Planned): Compile and flash without Keil
- Stage 4 (Planned): Port to STM32

## Build and Flash

**IDE:** Keil uVision 5 (MDK-ARM)

1. Open `Asteroid_Blaster.uvprojx` in Keil uVision 5
2. Build the project (F7 or Project → Build Target)
3. Flash to TM4C123 board via Keil's debugger
4. Open serial terminal at 9600 baud to play

**CRITICAL:** Comment out the clock configuration line in `RTE/Device/TM4C123GH6PM/system_TM4C123.c` (see notes.md line 2)

## Hardware Configuration

- **MCU:** TM4C123GH6PM (ARM Cortex-M4, 16 MHz system clock)
- **UART0:** PA0 (RX), PA1 (TX) at 9600 baud
- **TIMER0:** 32-bit periodic mode, 1 Hz interrupt (game tick)
- **GPIO:** Red LED for game over indication
- **Target:** TivaC LaunchPad development board

## Architecture

### Game Loop Structure

The game uses a **dual-interrupt architecture** with careful synchronization:

1. **TIMER0 Interrupt (1 Hz):** Sets `timer_ticked` flag
2. **Main Loop:** Processes game logic when `timer_ticked` is true:
   - Move bullets up
   - Check bullet-asteroid collisions
   - Move asteroids down
   - Check asteroid-ship collisions
   - Render all entities
   - Update counts
3. **UART0 Interrupt:** Handles player input (a/d for movement, space to shoot)

**Critical Sections:** Interrupts are disabled (`__disable_irq()` / `__enable_irq()`) during game state updates in main.c:36-55 to prevent race conditions between TIMER0 and UART0 handlers modifying shared state.

### Key Data Structures (include/assets.h)

- `board_t`: Central game state containing arrays of bullets, asteroids, and collision events
- `ship_t`, `bullet_t`, `asteroid_t`: Entity position and state
- `collision_event_t`: Temporary collision markers with duration-based decay

All game state is declared `volatile` because it's shared between interrupt handlers and main loop.

### Module Breakdown

**Core Game Modules:**
- `game.c/h`: Game initialization, start/restart, game over sequence
- `render.c/h`: UART output primitives, cursor control (VT100 escape sequences), entity rendering
- `collision.c/h`: AABB collision detection between ship/asteroids and bullets/asteroids
- `ship.c/h`: Ship movement with boundary checking
- `bullet.c/h`: Bullet spawning, movement, and lifecycle
- `asteroid.c/h`: Asteroid spawning with randomization, movement, boundary checking

**Hardware Abstraction:**
- `uart.c/h`: UART0 initialization, blocking/interrupt-driven I/O, input handler (UART0_Handler)
- `timer.c/h`: TIMER0 periodic interrupt setup, speed control for level progression (TIMER0A_Handler)
- `gpio.c/h`: LED control for game over indication
- `utils.c/h`: Integer-to-string conversion, delay, random number generation

**Configuration:**
- `config.c/h`: Game constants, playable area bounds, escape sequences, prompt strings
- `assets.h`: Entity type definitions and max counts

### Interrupt Handlers

- `UART0_Handler()` (uart.c:65): Processes 'a', 'd', space keys; modifies ship position and spawns bullets
- `TIMER0A_Handler()` (timer.c:52): Sets `timer_ticked = true` every 1 second

### Coordinate System

- **X (horizontal):** Column, range 2-21 (playable area)
- **Y (vertical):** Row, range 2-24 (playable area)
- **Origin:** Top-left is (1,1) in terminal space
- Ship spawns at (11, 24) - bottom center

### Known Issues and Solutions

**Race Conditions (notes.md:18-50):**
- **Problem:** Interleaved UART escape sequences when ship movement and timer interrupt access UART simultaneously
- **Solution:** `cursor_goto()` builds full escape sequence in buffer before atomic `output_string()` call (render.c:33-59)
- **Critical sections:** Main loop disables interrupts during entity movement/rendering

**Bullet-Asteroid Collision Bug (notes.md:56-61):**
- **Root cause:** Loop iteration variable modified inside loop body
- **Fix applied:** Separate movement and collision checking phases

**Asteroid Spawn Bug (notes.md:70-72):**
- **Root cause:** Operator precedence in modulo arithmetic
- **Solution:** Proper parenthesization for position calculation

**LED Blink Bug (notes.md:115-118):**
- **Root cause:** Static unsigned integer wraparound in blink function
- **Fix applied:** Remove static keyword from counter variable

## Development Patterns

### Adding New Features

When adding game features (powerups, new enemy types, etc.):
1. Define entity struct in `assets.h` following existing pattern (include `in_frame` flag)
2. Add to `board_t` if multiple instances needed
3. Implement spawn/move/erase functions in dedicated module
4. Add collision checks in `collision.c`
5. Integrate rendering in `render_game_entities()`
6. Update main loop in `main.c` to call movement/collision at appropriate times

### Memory Constraints

- **Stack:** Local variables only for small buffers
- **Global:** Game state (`game_board`, `ship`) must be global/static for ISR access
- **Volatile:** Required for all ISR-accessed variables to prevent compiler optimization bugs

### UART Output Guidelines

- Use `output_string()` for multi-character sequences (blocks until complete)
- Use `cursor_goto()` for positioning (atomic buffer-based implementation)
- Never call UART functions from both ISR and main simultaneously without critical sections
- VT100 escape sequences used: cursor positioning `\x1B[y;xH`, clear screen `\f`, hide/show cursor

### Game Speed Progression (main.c:72-74)

Each level halves `timer0_period_ticks`, doubling game speed. Minimum threshold is 0x50 (timer.c:44).

## Testing Notes

- **Debugging:** Use Keil debugger to inspect `game_board`, check entity `in_frame` flags and positions
- **Logic analyzer:** Can verify UART TX timing and escape sequence integrity (notes.md:52-54)
- **Common test cases:** Bullet-asteroid collision, out-of-bounds handling, ship collision, score tracking
- **Terminal:** Must support VT100 escape sequences (PuTTY, Tera Term, screen, minicom)
