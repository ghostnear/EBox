#pragma once

#include <stdint.h>

// Freeing callback.
typedef void(*dynarray_free_callback)(void*);

// Base type for a simple dynamic array with a freeing function.
typedef struct {
    void* data;
    uint32_t size;
    uint32_t capacity;
    uint32_t element_size;
    dynarray_free_callback free_callback;
} dynarray;

/*
 * First argument is the size of the elements, second argument is the callback to call for freeing them, if necessary.
 * If the callback is null, only free() will be used.  
 */
dynarray* dynarray_create(uint32_t, dynarray_free_callback);
void dynarray_push_back(dynarray*, void*);
void* dynarray_get(dynarray*, uint32_t);
void dynarray_remove(dynarray*, uint32_t);
void dynarray_free(void*);