#pragma once

#include "object.h"

typedef void stack_item_t;

typedef struct _stack_obj_t
{
    obj_t base;

    int item_size;
    int stack_size;
} stack_obj_t;

typedef struct
{
    int *item_size;
} stack_constructor_args_t;

typedef struct _stack_vtable_t
{
    bool (*push)(stack_obj_t *obj, const stack_item_t *node);
    void (*pop)(stack_obj_t *obj);
    bool (*top)(stack_obj_t *obj, stack_item_t *node);
    void (*clear)(stack_obj_t *obj);
    int (*size)(stack_obj_t *obj);
} stack_vtable_t;

void stack_delete(stack_obj_t *obj);
bool stack_push(stack_obj_t *obj, const stack_item_t *node);
void stack_pop(stack_obj_t *obj);
bool stack_top(stack_obj_t *obj, stack_item_t *node);
void stack_clear(stack_obj_t *obj);
int stack_size(stack_obj_t *obj);