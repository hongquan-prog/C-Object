#pragma once

#include "queue.h"
#include "link_list.h"

typedef struct _link_queue_obj_t
{
    queue_obj_t base;

    list_obj_t *list;
} link_queue_obj_t;

queue_obj_t *link_queue_create(int item_size);

bool link_queue_add(queue_obj_t *obj, const queue_item_t *node);
void link_queue_remove(queue_obj_t *obj);
bool link_queue_front(queue_obj_t *obj, queue_item_t *node);
void link_queue_clear(queue_obj_t *obj);
int link_queue_length(queue_obj_t *obj);