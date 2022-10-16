#pragma once

#include "object.h"

typedef void queue_item_t;

typedef struct _queue_obj_t
{
    obj_t base;

    int item_size;
    int queue_length;
} queue_obj_t;

typedef struct
{
    int *item_size;
} queue_constructor_args_t;

typedef struct _queue_vtable_t
{
    bool (*add)(queue_obj_t *obj, const queue_item_t *node);
    void (*remove)(queue_obj_t *obj);
    bool (*front)(queue_obj_t *obj, queue_item_t *node);
    void (*clear)(queue_obj_t *obj);
    int (*length)(queue_obj_t *obj);
} queue_vtable_t;

void queue_delete(queue_obj_t *obj);
bool queue_add(queue_obj_t *obj, const queue_item_t *node);
void queue_remove(queue_obj_t *obj);
bool queue_front(queue_obj_t *obj, queue_item_t *node);
void queue_clear(queue_obj_t *obj);
int queue_length(queue_obj_t *obj);