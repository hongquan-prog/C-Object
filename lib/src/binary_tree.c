#include "binary_tree.h"
#include <stdlib.h>
#include <string.h>

extern const obj_class_t g_tree_class;
static void binary_tree_constructor(obj_t *obj, obj_constructor_args_t *args);
static void binary_tree_destructor(obj_t *obj);

const static tree_vtable_t s_binary_tree_vtable = {
    .insert = binary_tree_insert,
    .remove = binary_tree_remove,
    .find = binary_tree_find,
    .degree = binary_tree_degree,
    .count = binary_tree_count,
    .height = binary_tree_height,
    .clear = binary_tree_clear,
    .begin = binary_tree_begin,
    .end = binary_tree_end,
    .next = binary_tree_next,
    .current = binary_tree_current};

const obj_class_t g_binary_tree_class = {
    .vtable = (obj_vtable_t *)&s_binary_tree_vtable,
    .base_class = &g_tree_class,
    .constructor_cb = binary_tree_constructor,
    .destructor_cb = binary_tree_destructor,
    .instance_size = sizeof(binary_tree_obj_t),
    .class_name = "binary tree"};

tree_obj_t *binary_tree_create(int item_size)
{
    tree_obj_t *obj = NULL;
    tree_constructor_args_t args = {0};

    if (item_size > 0)
    {
        /* pass args */
        args.item_size = &item_size;
        /* allocate memory and init data */
        obj = (tree_obj_t *)obj_class_create_obj(&g_binary_tree_class, (obj_constructor_args_t *)&args);

        if ((NULL == obj) || (NULL == ((binary_tree_obj_t *)obj)->queue))
        {
            tree_delete(obj);
            obj = NULL;
        }
    }

    return obj;
}

static binary_tree_node_t *binary_tree_new_node(tree_obj_t *obj)
{
    binary_tree_node_t *ret = NULL;

    ret = malloc(sizeof(binary_tree_node_t));

    if (ret)
    {
        ret->left = NULL;
        ret->right = NULL;
        ret->value = malloc(obj->item_size);

        if (NULL == ret->value)
        {
            free(ret);
            ret = NULL;
        }
    }

    return ret;
}

static void binary_tree_delete_node(binary_tree_node_t *node)
{
    if (node)
    {
        if (node->left)
        {
            binary_tree_delete_node(node->left);
        }

        if (node->right)
        {
            binary_tree_delete_node(node->right);
        }

        free(node->value);
        free(node);
    }
}

static void binary_tree_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    binary_tree_obj_t *tree = (binary_tree_obj_t *)obj;

    if (obj)
    {
        tree->queue = link_queue_create(sizeof(binary_tree_node_t *));
    }
}

static void binary_tree_destructor(obj_t *obj)
{
    binary_tree_obj_t *tree = (binary_tree_obj_t *)obj;

    if (tree)
    {
        binary_tree_delete_node((binary_tree_node_t *)tree->root);
        queue_delete(tree->queue);
    }
}

static binary_tree_node_t *find(binary_tree_obj_t *obj, binary_tree_node_t *node, tree_value_t *value)
{
    binary_tree_node_t *ret = NULL;

    if (node)
    {
        if (NULL == obj->equal)
        {
            if (0 == memcmp(node->value, value, obj->item_size))
            {
                return node;
            }

            if (node->left)
            {
                ret = find(obj, node->left, value);
            }

            if ((NULL == ret) && node->right)
            {
                ret = find(obj, node->right, value);
            }
        }
        else
        {
            if (obj->equal(node->value, value))
            {
                return node;
            }
            else if (node->left)
            {
                ret = find(obj, node->left, value);
            }
            else if ((NULL == ret) && node->right)
            {
                ret = find(obj, node->right, value);
            }
        }
    }

    return ret;
}

static bool insert(tree_obj_t *obj, binary_tree_node_t *node, binary_tree_pos_def pos)
{
    bool ret = false;
    binary_tree_obj_t *tree = (binary_tree_obj_t *)obj;

    if (obj && node)
    {
        if (NULL == obj->root)
        {
            ret = true;
            obj->root = (tree_node_t *)node;
            node->parent = NULL;
        }
        else
        {
            /* 此处查找是为了确定父节点的确存在于树中 */
            binary_tree_node_t *parent = find((binary_tree_obj_t *)obj, (binary_tree_node_t *)obj->root, node->parent->value);

            if (parent)
            {
                if (((BTREE_POS_LEFT == pos) || (BTREE_POS_ANY == pos)) && (NULL == parent->left))
                {
                    ret = true;
                    parent->left = node;
                }
                else if (((BTREE_POS_RIGHT == pos) || (BTREE_POS_ANY == pos)) && (NULL == parent->right))
                {
                    ret = true;
                    parent->right = node;
                }
            }
        }
    }

    return ret;
}

bool binary_tree_insert_to(tree_obj_t *obj, const tree_value_t *value, tree_node_t *parent, binary_tree_pos_def pos)
{
    bool ret = true;

    binary_tree_node_t *node = binary_tree_new_node(obj);

    if (node)
    {
        node->parent = parent;
        memcpy(node->value, value, obj->item_size);
        ret = insert(obj, node, pos);

        if (false == ret)
        {
            binary_tree_delete_node(node);
        }
    }

    return ret;
}

bool binary_tree_insert(tree_obj_t *obj, const tree_value_t *value, tree_node_t *parent)
{
    return binary_tree_insert_to(obj, value, parent, BTREE_POS_ANY);
}

tree_node_t *binary_tree_find(tree_obj_t *obj, tree_value_t *value)
{
    return (tree_node_t *)find((binary_tree_obj_t *)obj, (binary_tree_node_t *)obj->root, value);
}

bool binary_tree_remove(tree_obj_t *obj, tree_value_t *value)
{
    if (obj && value)
    {
        binary_tree_node_t *node = find((binary_tree_obj_t *)obj, (binary_tree_node_t *)obj->root, value);
        binary_tree_node_t *parent = (binary_tree_node_t *)(node->parent);

        if (node)
        {
            if (parent)
            {
                if (parent->left == node)
                {
                    parent->left = NULL;
                }
                else if (parent->right == node)
                {
                    parent->right = NULL;
                }
            }

            binary_tree_delete_node(node);
        }
    }
}

void binary_tree_clear(tree_obj_t *obj)
{
    binary_tree_obj_t *tree = (binary_tree_obj_t *)obj;

    if (tree)
    {
        binary_tree_delete_node((binary_tree_node_t *)tree->root);
        queue_clear(tree->queue);
    }
}

static int degree(binary_tree_node_t *node)
{
    int d = 0;
    int temp = 0;

    if (node)
    {
        d = !!(node->left) + !!(node->right);

        if (d < 2)
        {
            temp = degree(node->left);

            if (temp > d)
            {
                d = temp;
            }
        }

        if (d < 2)
        {

            temp = degree(node->right);

            if (temp > d)
            {
                d = temp;
            }
        }
    }

    return d;
}

static int count(binary_tree_node_t *node)
{
    int c = 0;

    if (node)
    {
        c = c + count(node->left) + count(node->right) + 1;
    }

    return c;
}

static int height(binary_tree_node_t *node)
{
    int h = 0;
    int temp = 0;

    if (node)
    {
        temp = height(node->left);

        if (temp > h)
        {
            h = temp;
        }

        temp = height(node->right);

        if (temp > h)
        {
            h = temp;
        }

        h += 1;
    }

    return h;
}

int binary_tree_degree(tree_obj_t *obj)
{
    return degree((binary_tree_node_t *)obj->root);
}

int binary_tree_count(tree_obj_t *obj)
{
    return count((binary_tree_node_t *)obj->root);
}

int binary_tree_height(tree_obj_t *obj)
{
    return height((binary_tree_node_t *)obj->root);
}

void binary_tree_begin(tree_obj_t *obj)
{
    binary_tree_obj_t *tree = (binary_tree_obj_t *)obj;

    if (obj->root)
    {
        queue_clear(tree->queue);
        queue_add(tree->queue, &obj->root);
    }
}

bool binary_tree_end(tree_obj_t *obj)
{
    binary_tree_obj_t *tree = (binary_tree_obj_t *)obj;

    return (queue_length(tree->queue) == 0);
}

void binary_tree_next(tree_obj_t *obj)
{
    binary_tree_node_t *node = NULL;
    binary_tree_obj_t *tree = (binary_tree_obj_t *)obj;

    if (queue_length(tree->queue) != 0)
    {
        queue_front(tree->queue, &node);
        queue_remove(tree->queue);

        if (node->left)
        {
            queue_add(tree->queue, &node->left);
        }

        if (node->right)
        {
            queue_add(tree->queue, &node->right);
        }
    }
}

tree_value_t *binary_tree_current(tree_obj_t *obj)
{
    binary_tree_node_t *node = NULL;
    binary_tree_obj_t *tree = (binary_tree_obj_t *)obj;
    
    if (!binary_tree_end(obj))
    {
        queue_front(tree->queue, &node);
        return node->value;
    }

    return NULL;
}