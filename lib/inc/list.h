#ifndef LIST_H
#define LIST_H

#include "object.h"
#include "operator.h"

typedef void list_node_t;

typedef struct _list_obj_t
{
    obj_t base;

    /* euual operator function reload */
    equal_operator_t equal;
    int item_size;
    int list_length;
} list_obj_t;

typedef struct _list_vtable_t
{
    bool (*insert)(list_obj_t *obj, int i, const list_node_t *node);
    void (*remove)(list_obj_t *obj, int i);
    int (*find)(list_obj_t *obj, const list_node_t *node);
    bool (*get)(list_obj_t *obj, int i, list_node_t *node);
    bool (*set)(list_obj_t *obj, int i, const list_node_t *node);
    void (*clear)(list_obj_t *obj);
    int (*length)(list_obj_t *obj);
    void (*begin)(list_obj_t *obj);
    bool (*end)(list_obj_t *obj);
    void (*next)(list_obj_t *obj);
    void (*pre)(list_obj_t *obj);
    list_node_t *(*current)(list_obj_t *obj);
} list_vtable_t;

typedef struct
{
    int *item_size;
} list_constructor_args_t;

void list_delete(list_obj_t *obj);
void list_reload_eual(list_obj_t *obj, equal_operator_t equal);
bool list_insert(list_obj_t *obj, int i, const list_node_t *node);
void list_remove(list_obj_t *obj, int i);
int list_find(list_obj_t *obj, const list_node_t *node);
bool list_get(list_obj_t *obj, int i, list_node_t *node);
bool list_set(list_obj_t *obj, int i, const list_node_t *node);
void list_clear(list_obj_t *obj);
int list_length(list_obj_t *obj);

void list_begin(list_obj_t *obj);
void list_next(list_obj_t *obj);
void list_pre(list_obj_t *obj);
bool list_end(list_obj_t *obj);
list_node_t *list_current(list_obj_t *obj);

#endif