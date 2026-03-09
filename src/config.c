#include "config.h"

// Escape sequences
const char *last_pos = "\x1B[u";
const char *move_up = "\x1B[1A";
const char *move_down = "\x1B[1B";
const char *move_left = "\x1B[1D";
const char *move_right = "\x1B[1C";
const char *save_pos = "\x1B[s";
const char *clear_display = "\x1B[2J";
const char *initial_pos = "\x1B[11;11H";
const char *hide_cursor = "\x1B[?25l";
const char *show_cursor = "\x1B[?25h";

// Prompts and board
const char *prompt_game_over = "\033[31;1mGAME OVER!\n\r";
const char *prompt_game_beginning =
    "Are you ready to start game? (Press Y)\n\r";
const char *prompt_game_rules =
    "Press 'w' to move up, 'a' to move left, 's' to move down, and 'd' to move "
    "right.\n\r Press SW1 to increase movement speed. \n\r If cursor '*' "
    "collides with a wall game ends.\n\r";
