#pragma once

#include "object.h"
#include "operator.h"

typedef void tree_value_t;

/******************************** tree_node_t *******************************************/

#define TREE_NODE_MEMBER         \
    struct _tree_node_t *parent; \
    tree_value_t *value;
typedef struct _tree_node_t
{
    TREE_NODE_MEMBER
} tree_node_t;

/***************************** tree_constructor_args_t ************************************/

#define TREE_CONSTRUCTOR_ARGS_MEMBER /* the size of value type */ \
    int *item_size;

typedef struct
{
    TREE_CONSTRUCTOR_ARGS_MEMBER
} tree_constructor_args_t;

/******************************** tree_obj_t *******************************************/

#define TREE_OBJ_MEMBER                  \
    OBJ_MEMBER                           \
    /* euual operator function reload */ \
    equal_operator_t equal;              \
    /* root node */                      \
    tree_node_t *root;                   \
    /* the size of value type */         \
    int item_size;

typedef struct _tree_obj_t
{
    TREE_OBJ_MEMBER
} tree_obj_t;

typedef struct _tree_vtable_t
{
    bool (*insert)(tree_obj_t *obj, const tree_value_t *value, tree_node_t *parent);
    bool (*remove)(tree_obj_t *obj, tree_value_t *value);
    tree_node_t *(*find)(tree_obj_t *obj, tree_value_t *value);
    int (*degree)(tree_obj_t *obj);
    int (*count)(tree_obj_t *obj);
    int (*height)(tree_obj_t *obj);
    void (*clear)(tree_obj_t *obj);
    void (*begin)(tree_obj_t *obj);
    bool (*end)(tree_obj_t *obj);
    void (*next)(tree_obj_t *obj);
    tree_value_t *(*current)(tree_obj_t *obj);
} tree_vtable_t;

void tree_delete(tree_obj_t *obj);
void tree_reload_equal(tree_obj_t *obj, equal_operator_t equal);
bool tree_insert(tree_obj_t *obj, const tree_value_t *value, tree_node_t *parent);
bool tree_remove(tree_obj_t *obj, tree_value_t *value);
tree_node_t *tree_find(tree_obj_t *obj, tree_value_t *value);
int tree_degree(tree_obj_t *obj);
int tree_count(tree_obj_t *obj);
int tree_height(tree_obj_t *obj);
void tree_clear(tree_obj_t *obj);
void tree_begin(tree_obj_t *obj);
bool tree_end(tree_obj_t *obj);
void tree_next(tree_obj_t *obj);
tree_value_t *tree_current(tree_obj_t *obj);
