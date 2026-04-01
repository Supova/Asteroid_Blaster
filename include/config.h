#ifndef CONFIG_H
#define CONFIG_H

// Game parameters
// all #defines and string constants (BOARD, prompts, macros)

//--------------------MACROS--------------------------------------------------------------------------------------
#define TAB '\t'
#define LINE_FEED '\n'
#define CLEAR_SCREEN '\f'
#define BEGINNING_OF_LINE '\r'

#define BLANK " "
#define SPACE ' '

#define LEFT 'a'
#define RIGHT 'd'

#define DELETE 0x08 // backspace

// Playable area boundaries (1-indexed)
#define PLAYABLE_MIN_Y 2
#define PLAYABLE_MAX_Y 24
#define PLAYABLE_MIN_X 2
#define PLAYABLE_MAX_X 21

#define SHIP_HEIGHT 1
#define SHIP_SPAWN_Y 24
#define SHIP_SPAWN_X 11

#define SHIP_SYMBOL "A"
#define ASTEROID_SYMBOL "O"
#define BULLET_SYMBOL "|"
#define COLLISION_SYMBOL "X"

// Escape sequences
extern const char *save_pos;
extern const char *initial_pos;
extern const char *hide_cursor;
extern const char *show_cursor;

// Board and prompts
extern const char *BOARD;
extern const char *prompt_game_welcome;
extern const char *prompt_game_beginning;
extern const char *prompt_game_rules ;
extern const char *prompt_game_over;

#endif