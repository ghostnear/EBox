#include "utils/memfree_list.h"

#include <stdlib.h>
#include <stdio.h>

static voidptr_list_node* allocated_list = NULL;

void voidptr_list_print_all(voidptr_list_node** list)
{
    if ((*list)->next != 0)
        voidptr_list_print_all((voidptr_list_node**)&((*list)->next));
}

void voidptr_list_add_internal(voidptr_list_node** list, void* ptr)
{
    voidptr_list_node* new_node = calloc(1, sizeof(voidptr_list_node));
    new_node->ptr = ptr;
    new_node->next = *list;
    *list = new_node;
    voidptr_list_print_all(list);
}

void voidptr_list_free_all_internal(voidptr_list_node** list)
{
    if((*list)->ptr != 0)
        free((*list)->ptr);
    if((*list)->next != 0)
        voidptr_list_free_all_internal((voidptr_list_node**)&((*list)->next));
    free(*list);
}

void memfree_add(void* ptr)
{
    voidptr_list_add_internal(&allocated_list, ptr);
}

void memfree_all()
{
    voidptr_list_free_all_internal(&allocated_list);
}