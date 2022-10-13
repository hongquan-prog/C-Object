#ifndef VECTOR_H
#define VECTOR_H

#include "list.h"

typedef struct
{
    int *item_size;
    void (*item_echo)(void *item);
    int *array_capacity;
} vector_construct_args_t;

typedef struct
{
    list_obj_t obj;
    char *array;
    int array_capacity;
    list_node_t *current;
} vector_obj_t;

list_obj_t *vector_create(int item_size, int length);

bool vector_insert(list_obj_t *obj, int i, const list_node_t * node);
void vector_remove(list_obj_t *obj, int i);
int vector_find(list_obj_t *obj, const list_node_t *node);
bool vector_get(list_obj_t *obj, int i, list_node_t *node);
bool vector_set(list_obj_t *obj, int i, const list_node_t *node);
int vector_length(list_obj_t *obj);

void vector_begin(list_obj_t *obj);
void vector_next(list_obj_t *obj);
bool vector_end(list_obj_t *obj);
list_node_t *vector_current(list_obj_t *obj);

#endif