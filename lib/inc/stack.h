#pragma once

#include "object.h"

typedef void stack_item_t;


/********************************* stack_constructor_args_t ***************************************/

#define STACK_CONSTRUCTOR_ARGS_MEMBER       int *item_size;

typedef struct
{
    STACK_CONSTRUCTOR_ARGS_MEMBER
} stack_constructor_args_t;

/************************************ stack_list_obj_t *******************************************/

#define STACK_OBJ_MEMBER                    OBJ_MEMBER \
                                            int item_size; \
                                            int stack_size;
typedef struct _stack_obj_t
{
    STACK_OBJ_MEMBER
} stack_obj_t;

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