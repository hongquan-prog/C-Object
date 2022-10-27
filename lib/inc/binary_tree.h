#pragma once

#include "tree.h"

typedef enum
{
    BTREE_POS_LEFT,
    BTREE_POS_RIGHT,
    BTREE_POS_ANY
} btree_pos_def;

typedef enum
{
    BTREE_TRIVERSAL_PRE,
    BTREE_TRIVERSAL_IN,
    BTREE_TRIVERSAL_POST,
    BTREE_TRIVERSAL_LEVEL
} btree_triversal_order_def;

/******************************** btree_node_t *******************************************/

#define BTREE_NODE_MEMBER               TREE_NODE_MEMBER \
                                        struct _btree_node_t *left; \
                                        struct _btree_node_t *right;

typedef struct _btree_node_t
{
    BTREE_NODE_MEMBER
} btree_node_t;

/******************************** btree_obj_t *******************************************/

#define BTREE_OBJ_MEMBER                TREE_OBJ_MEMBER
                
typedef struct _btree_obj_t
{
    BTREE_OBJ_MEMBER
} btree_obj_t;

