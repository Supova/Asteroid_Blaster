#include <stddef.h>
#include "circbuff.h"

void circbuff_init(circbuff_t *cb){
    if (cb == NULL){
        return;
    }

    cb->write = 0;
    cb->read = 0;
    cb->count = 0;
}

int circbuff_enqueue(circbuff_t *cb, entity_t data){
    if (cb == NULL){
        return CB_ERROR_NULL;
    }

    // reject data overwrite
    if (circbuff_is_full(cb)){
        return CB_ERROR_FULL;
    }

    cb->buffer[cb->write] = data;
    cb->write = (cb->write + 1) % cb->capacity;
    cb->count++;

    return CB_SUCCESS;
}

int circbuff_dequeue(circbuff_t *cb, entity_t *data){
    if (cb == NULL){
        return CB_ERROR_NULL;
    }

    if (circbuff_is_empty(cb)){
        return CB_ERROR_EMPTY;
    }

    *data = cb->buffer[cb->read];
    cb->read = (cb->read + 1) % cb->capacity;
    cb->count--;

    return CB_SUCCESS;
}

int circbuff_peek(circbuff_t *cb, entity_t *data){
    if (cb == NULL){
        return CB_ERROR_NULL;
    }

    if (circbuff_is_empty(cb)){
        return CB_ERROR_EMPTY;
    }

    *data = cb->buffer[cb->read];

    return CB_SUCCESS;
}

bool circbuff_is_full(const circbuff_t *cb){
    if (cb == NULL){
        return false;
    }

    return cb->count == cb->capacity;
}

bool circbuff_is_empty(const circbuff_t *cb){
    if (cb == NULL){
        return true;
    }

    return cb->count == 0;
}

uint16_t circbuff_count(const circbuff_t *cb){
     if (cb == NULL){
        return 0;
    }

    return cb->count;
}

void circbuff_reset(circbuff_t *cb){
     if (cb == NULL){
        return;
    }

    cb->write = 0;
    cb->read = 0;
    cb->count = 0;
}
