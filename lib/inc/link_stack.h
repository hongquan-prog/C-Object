#pragma once

#include "stack.h"
#include "link_list.h"

typedef struct _link_stack_obj_t
{
    stack_obj_t base;

    list_obj_t *list;
} link_stack_obj_t;

stack_obj_t *link_stack_create(int item_size);

bool link_stack_push(stack_obj_t *obj, const stack_item_t *node);
void link_stack_pop(stack_obj_t *obj);
bool link_stack_top(stack_obj_t *obj, stack_item_t *node);
void link_stack_clear(stack_obj_t *obj);
int link_stack_size(stack_obj_t *obj);