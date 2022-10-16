#include "queue.h"

static void queue_constructor(obj_t *obj, obj_constructor_args_t *args);

const obj_class_t g_queue_class = {
    .vtable = NULL,
    .base_class = NULL,
    .constructor_cb = queue_constructor,
    .destructor_cb = NULL,
    .instance_size = sizeof(queue_obj_t),
    .class_name = "queue" };

static void queue_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    queue_constructor_args_t *queue_args = (queue_constructor_args_t *)args;

    if (obj)
    {
        queue_obj_t *ret = (queue_obj_t *)obj;
        ret->item_size = *(queue_args->item_size);
        ret->queue_length = 0;
    }
}

void queue_delete(queue_obj_t *obj)
{
    obj_class_delete_obj((obj_t *)obj);
}

bool queue_add(queue_obj_t *obj, const queue_item_t *node)
{
    queue_vtable_t *vtable = (queue_vtable_t *)obj->base.class->vtable;
    
    if (vtable->add)
    {
        return vtable->add(obj, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "add function not exist in vtable");
    }
    
    return false;
}

void queue_remove(queue_obj_t *obj)
{
    queue_vtable_t *vtable = (queue_vtable_t *)obj->base.class->vtable;
    
    if (vtable->remove)
    {
        vtable->remove(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "remove function not exist in vtable");
    }
}

bool queue_front(queue_obj_t *obj, queue_item_t *node)
{
    queue_vtable_t *vtable = (queue_vtable_t *)obj->base.class->vtable;
    
    if (vtable->front)
    {
        return vtable->front(obj, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "front function not exist in vtable");
    }

    return false;
}

void queue_clear(queue_obj_t *obj)
{
    queue_vtable_t *vtable = (queue_vtable_t *)obj->base.class->vtable;
    
    if (vtable->clear)
    {
        vtable->clear(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "clear function not exist in vtable");
    }
}

int queue_length(queue_obj_t *obj)
{
    queue_vtable_t *vtable = (queue_vtable_t *)obj->base.class->vtable;
    
    if (vtable->length)
    {
        return vtable->length(obj);
    }
    else
    {
        return obj->queue_length;
    }

    return 0;
}