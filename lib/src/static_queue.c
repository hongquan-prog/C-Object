#include "static_queue.h"
#include <string.h>
#include <stdlib.h>

extern const obj_class_t g_queue_class;
static void static_queue_constructor(obj_t *obj, obj_constructor_args_t *args);
static void static_queue_destructor(obj_t *obj);

static const queue_vtable_t s_static_queue_vtable = {
    .add = static_queue_add,
    .remove = static_queue_remove,
    .front = static_queue_front,
    .clear = static_queue_clear,
    .length = NULL };

const obj_class_t g_static_queue_class = {
    .vtable = &s_static_queue_vtable,
    .base_class = &g_queue_class,
    .constructor_cb = static_queue_constructor,
    .destructor_cb = static_queue_destructor,
    .instance_size = sizeof(static_queue_obj_t),
    .class_name = "static queue" };

queue_obj_t *static_queue_create(int item_size, int capacity)
{
    queue_obj_t *obj = NULL;
    static_queue_constructor_args_t args = { 0 };
    
    if ((item_size > 0) && (capacity > 0))
    {
        args.queue_args.item_size = &item_size;
        args.queue_capacity = &capacity;

        obj = (queue_obj_t *)obj_class_create_obj(&g_static_queue_class, (obj_constructor_args_t *)&args);

        if ((NULL == obj) || (NULL == ((static_queue_obj_t *)obj)->array))
        {
            obj_class_delete_obj((obj_t *)obj);
            obj = NULL;
        }
    }

    return obj;
}

bool static_queue_add(queue_obj_t *obj, const queue_item_t *node)
{
    bool ret = false;
    static_queue_obj_t *queue = (static_queue_obj_t *)obj;
    
    if (obj->queue_length < queue->queue_capacity)
    {
        char *dest = queue->array + (obj->item_size * obj->queue_length);

        memcpy(dest, node, obj->item_size);
        queue->rear = (queue->rear + 1) % queue->queue_capacity;
        obj->queue_length++;
        ret = true;
    }

    return ret;
}

void static_queue_remove(queue_obj_t *obj)
{
    static_queue_obj_t *queue = (static_queue_obj_t *)obj;
    
    if ((obj->queue_length > 0))
    {
        queue->front = (queue->front + 1) % queue->queue_capacity;
        obj->queue_length--;
    }
}

bool static_queue_front(queue_obj_t *obj, queue_item_t *node)
{
    bool ret = false;
    static_queue_obj_t *queue = (static_queue_obj_t *)obj;

    if ((obj->queue_length > 0))
    {
        char *dest = queue->array + (obj->item_size * queue->front);
        memcpy(node, dest, obj->item_size);
        ret = true;
    }

    return ret;
}

void static_queue_clear(queue_obj_t *obj)
{
    static_queue_obj_t *queue = (static_queue_obj_t *)obj;
    
    queue->front = 0;
    queue->rear = 0;
    obj->queue_length = 0;
}

static void static_queue_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    queue_obj_t *queue = (queue_obj_t *)obj;
    static_queue_obj_t *static_queue = (static_queue_obj_t *)obj;
    static_queue_constructor_args_t *static_queue_args = (static_queue_constructor_args_t *)args;
    
    if (queue)
    {
        static_queue->queue_capacity = (*static_queue_args->queue_capacity);
        static_queue->array = malloc(queue->item_size * static_queue->queue_capacity);
        static_queue->front = 0;
        static_queue->rear = 0;
    }
}

static void static_queue_destructor(obj_t *obj)
{
    static_queue_obj_t *queue = (static_queue_obj_t *)obj;

    if (queue && queue->array)
    {
        free(queue->array);
    }
}