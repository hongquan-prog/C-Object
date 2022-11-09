#pragma once

#include "tree.h"
#include "link_queue.h"

typedef enum
{
    BTREE_POS_LEFT,
    BTREE_POS_RIGHT,
    BTREE_POS_ANY
} binary_tree_pos_def;

typedef enum
{
    BTREE_TRAVERSAL_PRE,
    BTREE_TRAVERSAL_IN,
    BTREE_TRAVERSAL_POST,
    BTREE_TRAVERSAL_LEVEL
} binary_tree_traversal_order_def;

/******************************** binary_tree_node_t *******************************************/

#define BTREE_NODE_MEMBER               TREE_NODE_MEMBER \
                                        struct _binary_tree_node_t *left; \
                                        struct _binary_tree_node_t *right;

typedef struct _binary_tree_node_t
{
    BTREE_NODE_MEMBER
} binary_tree_node_t;

/******************************** binary_tree_obj_t *******************************************/

#define BTREE_OBJ_MEMBER                TREE_OBJ_MEMBER \
                                        queue_obj_t *queue;

typedef struct _btree_obj_t
{
    BTREE_OBJ_MEMBER
} binary_tree_obj_t;

tree_obj_t *binary_tree_create(int item_size);
tree_node_t *binary_tree_find(tree_obj_t *obj, tree_value_t *value);
bool binary_tree_insert(tree_obj_t *obj, const tree_value_t *value, tree_node_t *parent);
bool binary_tree_insert_to(tree_obj_t *obj, const tree_value_t *value, tree_node_t *parent, binary_tree_pos_def pos);
bool binary_tree_remove(tree_obj_t *obj, tree_value_t *value);
void binary_tree_clear(tree_obj_t *obj);
int binary_tree_degree(tree_obj_t *obj);
int binary_tree_count(tree_obj_t *obj);
int binary_tree_height(tree_obj_t *obj);

void binary_tree_begin(tree_obj_t *obj);
bool binary_tree_end(tree_obj_t *obj);
void binary_tree_next(tree_obj_t *obj);
tree_value_t *binary_tree_current(tree_obj_t *obj);