#ifndef VECTOR_H
#define VECTOR_H

#include "list.h"

/*************************** vector_constructor_args_t ***********************************/

#define VECTOR_CONSTRUCTOR_ARGS_MEMBER  LIST_CONSTRUCTOR_ARGS_MEMBER \
                                        int *array_capacity;

typedef struct
{
    VECTOR_CONSTRUCTOR_ARGS_MEMBER
} vector_constructor_args_t;

/******************************** vector_obj_t *******************************************/

#define VECTOR_OBJ_MEMBER               LIST_OBJ_MEMBER \
                                        char *array; \
                                        int array_capacity; \
                                        list_node_t *current;

typedef struct
{
    VECTOR_OBJ_MEMBER
} vector_obj_t;

list_obj_t *vector_create(int item_size, int length);

bool vector_insert(list_obj_t *obj, int i, const list_node_t * node);
void vector_remove(list_obj_t *obj, int i);
int vector_find(list_obj_t *obj, const list_node_t *node);
bool vector_get(list_obj_t *obj, int i, list_node_t *node);
bool vector_set(list_obj_t *obj, int i, const list_node_t *node);
void vector_clear(list_obj_t *obj);
int vector_length(list_obj_t *obj);

void vector_begin(list_obj_t *obj);
void vector_next(list_obj_t *obj);
bool vector_end(list_obj_t *obj);
list_node_t *vector_current(list_obj_t *obj);

#endif