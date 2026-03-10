#ifndef CONFIG_H
#define CONFIG_H

// Game parameters
// all #defines and string constants (BOARD, prompts, macros)

//--------------------MACROS--------------------------------------------------------------------------------------
#define TAB '\t'
#define LINE_FEED '\n'
#define CLEAR_SCREEN '\f'
#define BEGINNING_OF_LINE '\r'

#define BULLET '|'
#define SPACE ' '

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

#define DELETE 0x08 // backspace
#define Y 'Y'

#define GO_UP 0x2
#define GO_DOWN 0x8
#define GO_LEFT 0x4
#define GO_RIGHT 0x1

// Rows and Columns start at 1, not 0
#define PLAYABLE_MIN_ROW 2
#define PLAYABLE_MAX_ROW 24
#define PLAYABLE_MIN_COL 2
#define PLAYABLE_MAX_COL 21

#define SHIP_CHAR 'A'
#define SHIP_SPAWN_Y 24
#define SHIP_SPAWN_X 11
#define SHIP_MAX_HEALTH 3

// Escape sequences
extern const char *last_pos;
extern const char *move_up;
extern const char *move_down;
extern const char *move_left;
extern const char *move_right;
extern const char *save_pos;
extern const char *clear_display;
extern const char *initial_pos;
extern const char *hide_cursor;
extern const char *show_cursor;

// Prompts and board
extern const char *prompt_game_welcome;
extern const char *prompt_game_beginning;
extern const char *prompt_game_rules ;
extern const char *prompt_game_over;


#endif