#include "stack.h"

static void stack_constructor(obj_t *obj, obj_constructor_args_t *args);

const obj_class_t g_stack_class = {
    .vtable = NULL,
    .base_class = NULL,
    .constructor_cb = stack_constructor,
    .destructor_cb = NULL,
    .instance_size = sizeof(stack_obj_t),
    .class_name = "stack" };

static void stack_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    stack_constructor_args_t *stack_args = (stack_constructor_args_t *)args;

    if (obj)
    {
        stack_obj_t *ret = (stack_obj_t *)obj;
        ret->item_size = *(stack_args->item_size);
        ret->stack_size = 0;
    }
}

void stack_delete(stack_obj_t *obj)
{
    obj_class_delete_obj((obj_t *)obj);
}

bool stack_push(stack_obj_t *obj, const stack_item_t *node)
{
    stack_vtable_t *vtable = (stack_vtable_t *)obj->base.class->vtable;
    
    if (vtable->push)
    {
        return vtable->push(obj, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "push function not exist in vtable");
        return false;
    }

}

void stack_pop(stack_obj_t *obj)
{
    stack_vtable_t *vtable = (stack_vtable_t *)obj->base.class->vtable;
    
    if (vtable->pop)
    {
        vtable->pop(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "pop function not exist in vtable");
    }
}

bool stack_top(stack_obj_t *obj, stack_item_t *node)
{
    stack_vtable_t *vtable = (stack_vtable_t *)obj->base.class->vtable;
    
    if (vtable->top)
    {
        return vtable->top(obj, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "top function not exist in vtable");
    }

    return false;
}

void stack_clear(stack_obj_t *obj)
{
    stack_vtable_t *vtable = (stack_vtable_t *)obj->base.class->vtable;
    
    if (vtable->clear)
    {
        vtable->clear(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "clear function not exist in vtable");
    }
}

int stack_size(stack_obj_t *obj)
{
    stack_vtable_t *vtable = (stack_vtable_t *)obj->base.class->vtable;
    
    if (vtable->size)
    {
        return vtable->size(obj);
    }
    else
    {
        return obj->stack_size;
    }

    return 0;
}