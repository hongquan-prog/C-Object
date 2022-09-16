#ifndef LIST_H
#define LIST_H

#include "err.h"

typedef void list_node_t;
struct _list_obj_t;
typedef struct _list_obj_t list_obj_t;

typedef struct _list_vtable_t
{
    bool (*insert)(list_obj_t *obj, int i, const list_node_t *node);
    void (*remove)(list_obj_t *obj, int i);
    int (*find)(list_obj_t *obj, const list_node_t *node);
    bool (*get)(list_obj_t *obj, int i, list_node_t *node);
    bool (*set)(list_obj_t *obj, int i, const list_node_t *node);
    int (*length)(list_obj_t *obj);
    void (*begin)(list_obj_t *obj);
    bool (*end)(list_obj_t *obj);
    void (*next)(list_obj_t *obj);
    void (*pre)(list_obj_t *obj);
    list_node_t *(*current)(list_obj_t *obj);
} list_vtable_t;

typedef struct _list_obj_class_t
{
    const struct _list_vtable_t *vtable;
    const struct _list_obj_class_t *base_class;
    void (*constructor_cb)(list_obj_t *class_p, int node_size);
    void (*destructor_cb)(list_obj_t *class_p);
    int instance_size;
    const char *type_name;
} list_obj_class_t;

struct _list_obj_t
{
    const list_obj_class_t *class_p;
    int item_size;
    int list_length;
};

list_obj_t *list_obj_class_create_obj(const list_obj_class_t *class_p, int item_size);

list_obj_t *list_delete(list_obj_t *obj);
void list_insert(list_obj_t *obj, int i, const list_node_t *node);
void list_remove(list_obj_t *obj, int i);
bool list_get(list_obj_t *obj, int i, list_node_t *node);
bool list_set(list_obj_t *obj, int i, const list_node_t *node);
int list_length(list_obj_t *obj);
int list_find(list_obj_t *obj, const list_node_t *node);

void list_begin(list_obj_t *obj);
void list_next(list_obj_t *obj);
void list_pre(list_obj_t *obj);
bool list_end(list_obj_t *obj);
list_node_t *list_current(list_obj_t *obj);

#endif