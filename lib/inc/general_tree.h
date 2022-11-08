#include "tree.h"
#include "link_list.h"
#include "link_queue.h"

/******************************** tree_node_t *******************************************/

#define GENERAL_TREE_NODE_MEMBER        TREE_NODE_MEMBER \
                                        /* a list to store child */ \
                                        list_obj_t *child;
typedef struct _general_tree_node_t
{
    GENERAL_TREE_NODE_MEMBER
} general_tree_node_t;

/******************************* general_tree_obj_t ************************************/
#define GENERAL_TREE_OBJ_MEMBER         TREE_OBJ_MEMBER \
                                        queue_obj_t *queue;

typedef struct _general_tree_obj_t
{
    GENERAL_TREE_OBJ_MEMBER
} general_tree_obj_t;

tree_obj_t *general_tree_create(int item_size);
bool general_tree_insert(tree_obj_t *obj, const tree_value_t *value, tree_node_t *parent);
bool general_tree_remove(tree_obj_t *obj, tree_value_t *value);
tree_node_t *general_tree_find(tree_obj_t *obj, tree_value_t *value);
int general_tree_degree(tree_obj_t *obj);
int general_tree_count(tree_obj_t *obj);
int general_tree_height(tree_obj_t *obj);
void general_tree_clear(tree_obj_t *obj);

void general_tree_begin(tree_obj_t *obj);
bool general_tree_end(tree_obj_t *obj);
void general_tree_next(tree_obj_t *obj);
tree_value_t *general_tree_current(tree_obj_t *obj);