#include "link_queue.h"
#include <string.h>
#include <stdlib.h>

extern const obj_class_t g_queue_class;
static void link_queue_constructor(obj_t *obj, obj_constructor_args_t *args);
static void link_queue_destructor(obj_t *obj);

static const queue_vtable_t s_link_queue_vtable = {
    .add = link_queue_add,
    .remove = link_queue_remove,
    .front = link_queue_front,
    .clear = link_queue_clear,
    .length = link_queue_length };

const obj_class_t g_link_queue_class = {
    .vtable = &s_link_queue_vtable,
    .base_class = &g_queue_class,
    .constructor_cb = link_queue_constructor,
    .destructor_cb = link_queue_destructor,
    .instance_size = sizeof(link_queue_obj_t),
    .class_name = "link queue" };

queue_obj_t *link_queue_create(int item_size)
{
    queue_obj_t *obj = NULL;
    queue_constructor_args_t args = { 0 };
    
    if ((item_size > 0))
    {
        args.item_size = &item_size;

        obj = (queue_obj_t *)obj_class_create_obj(&g_link_queue_class, (obj_constructor_args_t *)&args);

        if ((NULL == obj) || (NULL == ((link_queue_obj_t *)obj)->list))
        {
            obj_class_delete_obj((obj_t *)obj);
            obj = NULL;
        }
    }

    return obj;
}

bool link_queue_add(queue_obj_t *obj, const queue_item_t *node)
{
    link_queue_obj_t *queue = (link_queue_obj_t *)obj;
    
    return link_list_append(queue->list, node);

}

void link_queue_remove(queue_obj_t *obj)
{
    link_queue_obj_t *queue = (link_queue_obj_t *)obj;
    
    list_remove(queue->list, 0);
}

bool link_queue_front(queue_obj_t *obj, queue_item_t *node)
{
    link_queue_obj_t *queue = (link_queue_obj_t *)obj;

    return list_get(queue->list, 0, node);
}

int link_queue_length(queue_obj_t *obj)
{
    link_queue_obj_t *queue = (link_queue_obj_t *)obj;

    return list_length(queue->list);
}

void link_queue_clear(queue_obj_t *obj)
{
    link_queue_obj_t *queue = (link_queue_obj_t *)obj;
    
    list_clear(queue->list);
}

static void link_queue_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    queue_obj_t *queue = (queue_obj_t *)obj;
    link_queue_obj_t *link_queue = (link_queue_obj_t *)obj;
    queue_constructor_args_t *queue_args = (queue_constructor_args_t *)args;
    
    if (queue)
    {
        link_queue->list = link_list_create(*(queue_args->item_size));
    }
}

static void link_queue_destructor(obj_t *obj)
{
    link_queue_obj_t *queue = (link_queue_obj_t *)obj;

    if (queue && queue->list)
    {
        list_delete(queue->list);
    }
}