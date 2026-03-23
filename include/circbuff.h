#ifndef CIRCBUFF_H
#define CIRCBUFF_H

#include <stdint.h>
#include <stdbool.h>
#include "assets.h"

// Return codes
#define CB_SUCCESS 0
#define CB_ERROR_FULL -1
#define CB_ERROR_NULL -2
#define CB_ERROR_EMPTY -3

void circbuff_init(circbuff_t *cb);
int circbuff_enqueue(circbuff_t *cb, entity_t data);
int circbuff_dequeue(circbuff_t *cb, entity_t *data);
int circbuff_peek(circbuff_t *cb, entity_t *data);
bool circbuff_is_full(const circbuff_t *cb);
bool circbuff_is_empty(const circbuff_t *cb);
uint16_t circbuff_count(const circbuff_t *cb);
void circbuff_reset(circbuff_t *cb);

#endif