#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>

void output_character(char c);
void output_string(const char *str);
void cursor_goto(uint32_t y, uint32_t x);

#endif