#pragma once

// Freeing callback to be used with memfree module.
typedef void(*voidptr_list_free_callback)(void*);

// A primitive garbage collector's node used inside memfree.
typedef struct {
    void* pointer;
    voidptr_list_free_callback free_callback;
    void* next;
} voidptr_list_node;

/*
 * First argument is the pointer to free, second argument is the callback to call for freeing it, if necessary.
 * If the callback is null, only free() will be used.
 */ 
void memfree_add(void*, voidptr_list_free_callback);

/*
 * Call this to free all pointers added with memfree_add(), should be used in combination with atexit().
 */
void memfree_all();