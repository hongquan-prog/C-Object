#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "list.h"

typedef struct _link_list_node_t
{
    struct _link_list_node_t *next;
    void *user_data;
} link_list_node_t;

typedef struct _link_list_obj_t
{
    list_obj_t obj;
    link_list_node_t head;
    link_list_node_t *current;
} link_list_obj_t;


list_obj_t *link_list_create(int item_size);
bool link_list_insert(list_obj_t *obj, int i, const list_node_t *node);
void link_list_remove(list_obj_t *obj, int i);
int link_list_find(list_obj_t *obj, const list_node_t *node);
bool link_list_get(list_obj_t *obj, int i, list_node_t *node);

void link_list_begin(list_obj_t *obj);
void link_list_next(list_obj_t *obj);
bool link_list_end(list_obj_t *obj);
list_node_t* link_list_current(list_obj_t *obj);

#endif