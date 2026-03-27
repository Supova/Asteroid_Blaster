#include "TM4C123.h"
#include "render.h"
#include "utils.h"
#include "bullet.h"
#include "asteroid.h"
#include "ship.h"
#include "config.h"
#include "collision.h"

void output_character(char c) {
    while (UART0->FR & (1 << 5)); // WAIT (block) while TX FIFO is full
    UART0->DR = c; // Write char when FIFO has space
}

void output_string(const char *str) {
    while (*str) {
        output_character(*str++);
    } 
    // Function doesn't return until ALL characters are sent
}

// void cursor_goto(uint32_t y, uint32_t x) {
//   char buf[12];
//   output_character('\x1B');
//   output_character('[');
//   int2string((uint32_t)y, buf);
//   output_string(buf);
//   output_character(';');
//   int2string((uint32_t)x, buf);
//   output_string(buf);
//   output_character('H');
// }

void cursor_goto(uint32_t y, uint32_t x) {
    char buf[20];
    uint8_t index = 0;
    
    buf[index++] = '\x1B';
    buf[index++] = '[';
    
    // Append Y coordinate
    char temp[12];
    int2string(y, temp);
    for (uint8_t i = 0; temp[i] != '\0'; i++) {
        buf[index++] = temp[i];
    }
    
    buf[index++] = ';';
    
    // Append X coordinate
    int2string(x, temp);
    for (uint8_t i = 0; temp[i] != '\0'; i++) {
        buf[index++] = temp[i];
    }
    
    buf[index++] = 'H';
    buf[index] = '\0';

    output_string(buf);  // Single atomic call
}

void render_game_entities(volatile board_t *game_board, volatile ship_t ship) {
    // Draw all active bullets
    for (int i = 0; i < MAX_NUM_BULLETS; i++) {
        if (game_board->bullets[i].in_frame) {
            bullet_draw(game_board->bullets[i].y, game_board->bullets[i].x);
        }
    }

    // Draw all active asteroids
    for (int j = 0; j < MAX_NUM_ASTEROIDS; j++) {
        if (game_board->asteroids[j].in_frame) {
            asteroid_draw(game_board->asteroids[j].y, game_board->asteroids[j].x);
        }
    }

<<<<<<< Updated upstream
=======
    // Draw collision markers
    for (int k = 0; k < game_board->collision_count; k++) {
        collision_draw(game_board->collisions[k].y, game_board->collisions[k].x);
    }

>>>>>>> Stashed changes
    // Draw ship
    ship_draw(ship.y, ship.x);
}