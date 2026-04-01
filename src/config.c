#include "config.h"

// Escape sequences
const char *save_pos = "\x1B[s";
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
    "right.\n\rIf an asteroid collides with the ship, game ends.\n\r\n\r";
const char *prompt_game_beginning =
    "Are you ready to start playing? (Press Y)\n\r";
const char *prompt_game_over = "\033[31;1mGAME OVER!\n\r";
