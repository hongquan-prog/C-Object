#include "static_stack.h"
#include <string.h>
#include <stdlib.h>

extern const obj_class_t g_stack_class;
static void static_stack_constructor(obj_t *obj, obj_constructor_args_t *args);
static void static_stack_destructor(obj_t *obj);

static const stack_vtable_t s_static_stack_vtable = {
    .push = static_stack_push,
    .pop = static_stack_pop,
    .top = static_stack_top,
    .clear = static_stack_clear,
    .size = NULL };

const obj_class_t g_static_stack_class = {
    .vtable = &s_static_stack_vtable,
    .base_class = &g_stack_class,
    .constructor_cb = static_stack_constructor,
    .destructor_cb = static_stack_destructor,
    .instance_size = sizeof(static_stack_obj_t),
    .class_name = "static stack" };

stack_obj_t *static_stack_create(int item_size, int capacity)
{
    stack_obj_t *obj = NULL;
    static_stack_constructor_args_t args = { 0 };
    
    if ((item_size > 0) && (capacity > 0))
    {
        args.item_size = &item_size;
        args.stack_capacity = &capacity;

        obj = (stack_obj_t *)obj_class_create_obj(&g_static_stack_class, (obj_constructor_args_t *)&args);

        if ((NULL == obj) || (NULL == ((static_stack_obj_t *)obj)->array))
        {
            obj_class_delete_obj((obj_t *)obj);
            obj = NULL;
        }
    }

    return obj;
}

bool static_stack_push(stack_obj_t *obj, const stack_item_t *node)
{
    bool ret = false;
    static_stack_obj_t *stack = (static_stack_obj_t *)obj;
    
    if (obj->stack_size < stack->stack_capacity)
    {
        int pos = (stack->top + obj->stack_size) % stack->stack_capacity;
        char *dest = stack->array + (obj->item_size * pos);

        memcpy(dest, node, obj->item_size);
        obj->stack_size++;
        ret = true;
    }

    return ret;
}

void static_stack_pop(stack_obj_t *obj)
{
    static_stack_obj_t *stack = (static_stack_obj_t *)obj;
    
    if ((obj->stack_size > 0))
    {
        stack->top = (stack->top + 1) % stack->stack_capacity;
        obj->stack_size--;
    }
}

bool static_stack_top(stack_obj_t *obj, stack_item_t *node)
{
    bool ret = false;
    static_stack_obj_t *stack = (static_stack_obj_t *)obj;

    if ((obj->stack_size > 0))
    {
        char *dest = stack->array + (obj->item_size * stack->top);
        memcpy(node, dest, obj->item_size);
        ret = true;
    }

    return ret;
}

void static_stack_clear(stack_obj_t *obj)
{
    static_stack_obj_t *stack = (static_stack_obj_t *)obj;
    
    stack->top = 0;
    obj->stack_size = 0;
}

static void static_stack_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    stack_obj_t *stack = (stack_obj_t *)obj;
    static_stack_obj_t *static_stack = (static_stack_obj_t *)obj;
    static_stack_constructor_args_t *static_stack_args = (static_stack_constructor_args_t *)args;
    
    if (stack)
    {
        static_stack->stack_capacity = (*static_stack_args->stack_capacity);
        static_stack->array = malloc(stack->item_size * static_stack->stack_capacity);
        static_stack->top = 0;
    }
}

static void static_stack_destructor(obj_t *obj)
{
    static_stack_obj_t *stack = (static_stack_obj_t *)obj;

    if (stack && stack->array)
    {
        free(stack->array);
    }
}