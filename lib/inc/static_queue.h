#pragma once

#include "queue.h"

typedef struct _static_queue_obj_t
{
    queue_obj_t base;

    char *array;
    int queue_capacity;
    int front;
    int rear;
} static_queue_obj_t;

typedef struct
{
    queue_constructor_args_t queue_args;

    int *queue_capacity;
} static_queue_constructor_args_t;

queue_obj_t *static_queue_create(int item_size, int capacity);

bool static_queue_add(queue_obj_t *obj, const queue_item_t *node);
void static_queue_remove(queue_obj_t *obj);
bool static_queue_front(queue_obj_t *obj, queue_item_t *node);
void static_queue_clear(queue_obj_t *obj);