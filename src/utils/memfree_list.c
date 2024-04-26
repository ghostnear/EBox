#include "utils/memfree_list.h"

#include <stdlib.h>

static voidptr_list_node* allocated_list = NULL;

void voidptr_list_add_internal(voidptr_list_node** self, void* pointer, voidptr_list_free_callback callback)
{
    voidptr_list_node* new_node = calloc(1, sizeof(voidptr_list_node));
    new_node->pointer = pointer;
    new_node->next = *self;
    new_node->free_callback = callback;
    *self = new_node;
}

void voidptr_list_free_all_internal(voidptr_list_node** self)
{
    if((*self)->pointer != NULL)
    {
        if((*self)->free_callback != NULL)
            (*self)->free_callback((*self)->pointer);
        else
            free((*self)->pointer);
    }
    // TODO: make this not recursive thanks.
    if((*self)->next != NULL)
        voidptr_list_free_all_internal((voidptr_list_node**)&((*self)->next));
    free(*self);
}

void memfree_add(void* thing, voidptr_list_free_callback callback)
{
    voidptr_list_add_internal(&allocated_list, thing, callback);
}

void memfree_all()
{
    if(allocated_list == NULL)
        return;

    voidptr_list_free_all_internal(&allocated_list);
}