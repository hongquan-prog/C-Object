#ifndef DUAL_LINK_LIST_H
#define DUAL_LINK_LIST_H

#include "link_list.h"

typedef struct _dual_link_list_node_t
{
    struct _dual_link_list_node_t *next;
    struct _dual_link_list_node_t *pre;
    void *user_data;
} dual_link_list_node_t;

typedef struct _dual_link_list_obj_t
{
    list_obj_t obj;
    dual_link_list_node_t head;
    dual_link_list_node_t *current;
} dual_link_list_obj_t;

list_obj_t *dual_link_list_create(int item_size);
bool dual_link_list_insert(list_obj_t *list, int i, const list_node_t *node);
void dual_link_list_remove(list_obj_t *list, int i);
int dual_link_list_find(list_obj_t *list, const list_node_t *node);
bool dual_link_list_set(list_obj_t *obj, int i, const list_node_t *node);
bool dual_link_list_get(list_obj_t *list, int i, list_node_t *node);
void dual_link_list_destroy(list_obj_t *list);
list_node_t *dual_link_list_position(list_obj_t *list, int position);

void dual_link_list_begin(list_obj_t *list);
void dual_link_list_next(list_obj_t *list);
void dual_link_list_pre(list_obj_t *list);
bool dual_link_list_end(list_obj_t *list);
list_node_t *dual_link_list_current(list_obj_t *list);

#endif