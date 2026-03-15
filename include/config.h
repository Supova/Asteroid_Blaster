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

// Playable area boundaries (1-indexed)
#define PLAYABLE_MIN_Y 2
#define PLAYABLE_MAX_Y 24
#define PLAYABLE_MIN_X 2
#define PLAYABLE_MAX_X 21

#define SHIP_HEIGHT 1
#define SHIP_SPAWN_Y 24
#define SHIP_SPAWN_X 11
#define SHIP_MAX_HEALTH 3

#define SHIP_SYMBOL "A"
#define ASTEROID_SYMBOL "O"
#define BULLET_SYMBOL "|"
#define COLLISION_SYMBOL "X"

#define STARTING_SPEED 0xF42400

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

// Board and prompts
extern const char *BOARD;
extern const char *prompt_game_welcome;
extern const char *prompt_game_beginning;
extern const char *prompt_game_rules ;
extern const char *prompt_game_over;


#endif