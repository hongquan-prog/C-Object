#pragma once

#include "stack.h"

typedef struct _static_stack_obj_t
{
    stack_obj_t base;

    char *array;
    int stack_capacity;
    int top;
} static_stack_obj_t;

typedef struct
{
    stack_constructor_args_t stack_args;

    int *stack_capacity;
} static_stack_constructor_args_t;

stack_obj_t *static_stack_create(int item_size, int capacity);

bool static_stack_push(stack_obj_t *obj, const stack_item_t *node);
void static_stack_pop(stack_obj_t *obj);
bool static_stack_top(stack_obj_t *obj, stack_item_t *node);
void static_stack_clear(stack_obj_t *obj);