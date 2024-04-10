#pragma once

// This thing is more like a primitive garbage collector than anything else.

typedef struct {
    void* ptr;
    void* next;
} voidptr_list_node;

void memfree_add(void*);
void memfree_all();