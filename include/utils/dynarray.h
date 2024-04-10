#pragma once

#include <stdint.h>

typedef void(*dynarray_free_callback)(void*);

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

/*
 * Add a copy of an element to the array.
 */
void dynarray_push_back(dynarray*, void*);

/*
 * Get a pointer to the element at the specified index.
 */
void* dynarray_get(dynarray*, uint32_t);

/*
 * Remove the element at the specified index.
 */
void dynarray_remove(dynarray*, uint32_t);

/*
 * Free the dynamic array.
 */
void dynarray_free(void*);