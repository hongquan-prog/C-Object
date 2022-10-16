#ifndef DUAL_CIRCLE_LIST_H
#define DUAL_CIRCLE_LIST_H

#include "dual_link_list.h"

list_obj_t *dual_circle_list_create(int item_size);
void dual_circle_list_destroy(list_obj_t *list);
bool dual_circle_list_push_back(list_obj_t *list, list_node_t * node);
bool dual_circle_list_push_front(list_obj_t *list, list_node_t * node);
void dual_circle_list_pop_front(list_obj_t *list, list_node_t * node);
void dual_circle_list_pop_back(list_obj_t *list, list_node_t * node);
bool dual_circle_list_insert(list_obj_t *list, int i, const list_node_t * node);
void dual_circle_list_remove(list_obj_t *list, int i);
bool dual_circle_list_get(list_obj_t *obj, int i, list_node_t *node);
bool dual_circle_list_set(list_obj_t *obj, int i, const list_node_t *node);

bool dual_circle_list_end(list_obj_t *list);

#endif