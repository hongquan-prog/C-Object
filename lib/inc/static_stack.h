#pragma once

#include "stack.h"

/******************************* static_stack_constructor_args_t ******************************/

#define STATIC_STACK_CONSTRUCTOR_ARGS_MEMBER            STACK_CONSTRUCTOR_ARGS_MEMBER \
                                                        int *stack_capacity;
typedef struct
{
    STATIC_STACK_CONSTRUCTOR_ARGS_MEMBER
} static_stack_constructor_args_t;

/******************************* static_stack_obj_t ******************************/

#define STATIC_STACK_OBJ_MEMBER                         STACK_OBJ_MEMBER \
                                                        char *array; \
                                                        int stack_capacity; \
                                                        int top;
typedef struct _static_stack_obj_t
{
    STATIC_STACK_OBJ_MEMBER
} static_stack_obj_t;



stack_obj_t *static_stack_create(int item_size, int capacity);

bool static_stack_push(stack_obj_t *obj, const stack_item_t *node);
void static_stack_pop(stack_obj_t *obj);
bool static_stack_top(stack_obj_t *obj, stack_item_t *node);
void static_stack_clear(stack_obj_t *obj);