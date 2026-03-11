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

// Board and prompt
const char *BOARD = " -------------------- \n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    "|                    |\n\r"
                    " -------------------- ";
                    
const char *prompt_game_welcome = "\n\rWelcome to Asteroid Blaster!\n\r"
                                  "Can you survive by destroying incoming "
                                  "asteroids and save your crew?\n\r\n\r";

const char *prompt_game_rules =
    "Press 'a' to move left and 'd' to move "
    "right.\n\rPress SW1 to increase movement speed.\n\rIf an asteroid "
    "collides with the ship, game ends.\n\r\n\r";
const char *prompt_game_beginning =
    "Are you ready to start playing? (Press Y)\n\r";
const char *prompt_game_over = "\033[31;1mGAME OVER!\n\r";
