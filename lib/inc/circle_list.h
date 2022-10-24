#ifndef CIRCLE_LIST_H
#define CIRCLE_LIST_H

#include "link_list.h"

typedef link_list_obj_t circle_list_obj_t;

list_obj_t *circle_list_create(int item_size);
bool circle_list_insert(list_obj_t *obj, int i, const list_node_t *node);
void circle_list_remove(list_obj_t *obj, int i);
bool circle_list_get(list_obj_t *obj, int i, list_node_t *node);
bool circle_list_set(list_obj_t *obj, int i, const list_node_t *node);
void circle_list_clear(list_obj_t *obj);
bool circle_list_end(list_obj_t *obj);

#endif