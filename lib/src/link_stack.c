#include "link_stack.h"
#include <string.h>
#include <stdlib.h>

extern const obj_class_t g_stack_class;
static void link_stack_constructor(obj_t *obj, obj_constructor_args_t *args);
static void link_stack_destructor(obj_t *obj);

static const stack_vtable_t s_link_stack_vtable = {
    .push = link_stack_push,
    .pop = link_stack_pop,
    .top = link_stack_top,
    .clear = link_stack_clear,
    .size = link_stack_size};

const obj_class_t g_link_stack_class = {
    .vtable = &s_link_stack_vtable,
    .base_class = &g_stack_class,
    .constructor_cb = link_stack_constructor,
    .destructor_cb = link_stack_destructor,
    .instance_size = sizeof(link_stack_obj_t),
    .class_name = "link stack"};

stack_obj_t *link_stack_create(int item_size)
{
    stack_obj_t *obj = NULL;
    stack_constructor_args_t args = {0};

    if ((item_size > 0))
    {
        args.item_size = &item_size;

        obj = (stack_obj_t *)obj_class_create_obj(&g_link_stack_class, (obj_constructor_args_t *)&args);

        if ((NULL == obj) || (NULL == ((link_stack_obj_t *)obj)->list))
        {
            obj_class_delete_obj((obj_t *)obj);
            obj = NULL;
        }
    }

    return obj;
}

bool link_stack_push(stack_obj_t *obj, const stack_item_t *node)
{
    link_stack_obj_t *stack = (link_stack_obj_t *)obj;

    return link_list_insert(stack->list, 0, node);
}

void link_stack_pop(stack_obj_t *obj)
{
    link_stack_obj_t *stack = (link_stack_obj_t *)obj;

    list_remove(stack->list, 0);
}

bool link_stack_top(stack_obj_t *obj, stack_item_t *node)
{
    link_stack_obj_t *stack = (link_stack_obj_t *)obj;

    return list_get(stack->list, 0, node);
}

int link_stack_size(stack_obj_t *obj)
{
    link_stack_obj_t *stack = (link_stack_obj_t *)obj;

    return list_length(stack->list);
}

void link_stack_clear(stack_obj_t *obj)
{
    link_stack_obj_t *stack = (link_stack_obj_t *)obj;

    list_clear(stack->list);
}

static void link_stack_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    stack_obj_t *stack = (stack_obj_t *)obj;
    link_stack_obj_t *link_stack = (link_stack_obj_t *)obj;
    stack_constructor_args_t *stack_args = (stack_constructor_args_t *)args;

    if (stack)
    {
        link_stack->list = link_list_create(*(stack_args->item_size));
    }
}

static void link_stack_destructor(obj_t *obj)
{
    link_stack_obj_t *stack = (link_stack_obj_t *)obj;

    if (stack && stack->list)
    {
        list_delete(stack->list);
    }
}