#include "utils/dynarray.h"

#include <stdlib.h>
#include <memory.h>

dynarray* dynarray_create(uint32_t element_size, dynarray_free_callback free_callback)
{
    dynarray* self = calloc(1, sizeof(dynarray));
    self->size = 0;
    self->capacity = 4;
    self->element_size = element_size;
    self->free_callback = free_callback;
    self->data = calloc(self->capacity, element_size);
    return self;
}

void dynarray_push_back(dynarray* self, void* element)
{
    if(self->size == self->capacity)
    {
        self->capacity *= 2;
        self->data = realloc(self->data, self->capacity * self->element_size);
    }
    memcpy(self->data + (self->size * self->element_size), element, self->element_size);
    self->size++;
}

void dynarray_remove(dynarray* self, uint32_t index)
{
    if(index >= self->size)
        return;
    if(self->free_callback != NULL)
        self->free_callback(self->data + (index * self->element_size));
    memmove(self->data + (index * self->element_size), self->data + ((index + 1) * self->element_size), (self->size - index - 1) * self->element_size);
    self->size--;
    if(self->size < self->capacity / 4)
    {
        self->capacity /= 4;
        self->data = realloc(self->data, self->capacity * self->element_size);
    }
}

void* dynarray_get(dynarray* self, uint32_t index)
{
    if(index >= self->size)
        return NULL;
    return self->data + (index * self->element_size);
}

void dynarray_free(void* self)
{
    const dynarray* array = (dynarray*)self;
    if(array->free_callback != NULL)
    {
        for(uint32_t i = 0; i < array->size; i++)
            array->free_callback(array->data + (i * array->element_size));
    }
    free(array->data);
    free((void*)array);
}