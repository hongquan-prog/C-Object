#include "general_tree.h"
#include <stdlib.h>
#include <string.h>

extern const obj_class_t g_tree_class;
static void general_tree_constructor(obj_t *obj, obj_constructor_args_t *args);
static void general_tree_destructor(obj_t *obj);

const static tree_vtable_t s_general_tree_vtable = {
    .insert = general_tree_insert,
    .remove = general_tree_remove,
    .find = general_tree_find,
    .degree = general_tree_degree,
    .count = general_tree_count,
    .height = general_tree_height,
    .clear = general_tree_clear,
    .begin = general_tree_begin,
    .end = general_tree_end,
    .next = general_tree_next,
    .current = general_tree_current};

const obj_class_t g_general_tree_class = {
    .vtable = (obj_vtable_t *)&s_general_tree_vtable,
    .base_class = &g_tree_class,
    .constructor_cb = general_tree_constructor,
    .destructor_cb = general_tree_destructor,
    .instance_size = sizeof(general_tree_obj_t),
    .class_name = "general tree"};

tree_obj_t *general_tree_create(int item_size)
{
    tree_obj_t *obj = NULL;
    tree_constructor_args_t args = {0};

    if (item_size > 0)
    {
        /* pass args */
        args.item_size = &item_size;
        /* allocate memory and init data */
        obj = (tree_obj_t *)obj_class_create_obj(&g_general_tree_class, (obj_constructor_args_t *)&args);

        if ((NULL == obj) || (NULL == ((general_tree_obj_t *)obj)->queue))
        {
            tree_delete(obj);
            obj = NULL;
        }
    }

    return obj;
}

static general_tree_node_t *general_tree_new_node(tree_obj_t *obj)
{
    general_tree_node_t *ret = malloc(sizeof(general_tree_node_t));

    if (ret)
    {
        ret->child = link_list_create(sizeof(general_tree_node_t *));
        ret->value = malloc(obj->item_size);

        if ((NULL == ret->child) || (NULL == ret->value))
        {
            free(ret->value);
            list_delete(ret->child);
            free(ret);
            ret = NULL;
        }
    }

    return ret;
}

static void general_tree_delete_node(general_tree_node_t *node)
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        if (node->child)
        {
            for (list_begin(node->child); !list_end(node->child); list_next(node->child))
            {
                general_tree_node_t **child = list_current(node->child);
                general_tree_delete_node(*child);
            }

            list_delete(node->child);
            free(node->value);
            free(node);
        }
    }
}

static general_tree_node_t *general_tree_find_from_node(tree_obj_t *obj, general_tree_node_t *node, tree_value_t *value)
{
    general_tree_node_t *ret = NULL;

    if (node != NULL)
    {
        if (NULL == obj->equal)
        {
            if (0 == memcmp(value, node->value, obj->item_size))
            {
                return node;
            }
            else
            {
                for (list_begin(node->child); !list_end(node->child) && (ret == NULL); list_next(node->child))
                {
                    general_tree_node_t **temp = list_current(node->child);
                    ret = general_tree_find_from_node(obj, *temp, value);
                }
            }
        }
        else
        {
            if (obj->equal(value, node->value))
            {
                return node;
            }
            else
            {
                for (list_begin(node->child); !list_end(node->child) && (ret == NULL); list_next(node->child))
                {
                    general_tree_node_t **temp = list_current(node->child);
                    ret = general_tree_find_from_node(obj, *temp, value);
                }
            }
        }
    }

    return ret;
}

static bool general_tree_insert_node(tree_obj_t *obj, tree_node_t *node)
{
    bool ret = false;

    if (node != NULL)
    {
        if (obj->root == NULL)
        {
            node->parent = NULL;
            obj->root = node;
        }
        else
        {
            general_tree_node_t *parent = general_tree_find_from_node(obj, (general_tree_node_t *)obj->root, node->parent->value);

            if (parent != NULL)
            {
                if (list_find(parent->child, &node) < 0)
                {
                    ret = list_insert(parent->child, 0, &node);
                }
            }
        }
    }

    return ret;
}

static void general_tree_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    general_tree_obj_t *tree = (general_tree_obj_t *)obj;

    if (obj)
    {
        tree->queue = link_queue_create(sizeof(general_tree_node_t *));
    }
}

static void general_tree_destructor(obj_t *obj)
{
    general_tree_obj_t *tree = (general_tree_obj_t *)obj;

    if (tree)
    {
        general_tree_delete_node((general_tree_node_t *)tree->root);
        queue_delete(tree->queue);
    }
}

tree_node_t *general_tree_find(tree_obj_t *obj, tree_value_t *value)
{
    return (tree_node_t *)general_tree_find_from_node(obj, (general_tree_node_t *)obj->root, value);
}

bool general_tree_insert(tree_obj_t *obj, const tree_value_t *value, tree_node_t *parent)
{
    bool ret = false;

    if (value != NULL)
    {
        tree_node_t *node = (tree_node_t *)general_tree_new_node(obj);

        if (node)
        {
            node->parent = parent;
            memcpy(node->value, value, obj->item_size);
            ret = general_tree_insert_node(obj, node);
        }
    }

    return ret;
}

bool general_tree_remove(tree_obj_t *obj, tree_value_t *value)
{
    int pos = -1;
    bool ret = false;
    general_tree_node_t *node = (general_tree_node_t *)general_tree_find(obj, value);

    if (node != NULL)
    {
        pos = list_find(((general_tree_node_t *)node->parent)->child, &node);
        list_remove(((general_tree_node_t *)node->parent)->child, pos);
        general_tree_delete_node(node);
    }

    return ret;
}

static int degree(tree_node_t *node)
{
    int ret = 0;
    int d = 0;
    general_tree_node_t *g_node = (general_tree_node_t *)node;

    if (g_node)
    {
        ret = list_length(g_node->child);

        for (list_begin(g_node->child); !list_end(g_node->child); list_next(g_node->child))
        {
            tree_node_t **temp = list_current(g_node->child);
            d = degree(*temp);

            if (d > ret)
            {
                ret = d;
            }
        }
    }

    return ret;
}

static int count(tree_node_t *node)
{
    int ret = 0;
    general_tree_node_t *g_node = (general_tree_node_t *)node;

    if (node)
    {
        ret = 1;

        for (list_begin(g_node->child); !list_end(g_node->child); list_next(g_node->child))
        {
            tree_node_t **temp = list_current(g_node->child);
            ret += count(*temp);
        }
    }

    return ret;
}

static int height(tree_node_t *node)
{
    int h = 0;
    int ret = 0;
    general_tree_node_t *g_node = (general_tree_node_t *)node;

    if (node)
    {
        for (list_begin(g_node->child); !list_end(g_node->child); list_next(g_node->child))
        {
            tree_node_t **temp = list_current(g_node->child);
            h = height(*temp);

            if (h > ret)
            {
                ret = h;
            }
        }

        ret = ret + 1;
    }

    return ret;
}

int general_tree_degree(tree_obj_t *obj)
{
    return degree(obj->root);
}

int general_tree_count(tree_obj_t *obj)
{
    return count(obj->root);
}

int general_tree_height(tree_obj_t *obj)
{
    return height(obj->root);
}

void general_tree_clear(tree_obj_t *obj)
{
    general_tree_obj_t *tree = (general_tree_obj_t *)obj;

    if (tree)
    {
        general_tree_delete_node((general_tree_node_t *)tree->root);
        queue_clear(tree->queue);
        tree->root = NULL;
    }
}

void general_tree_begin(tree_obj_t *obj)
{
    general_tree_obj_t *tree = (general_tree_obj_t *)obj;

    queue_clear(tree->queue);
    queue_add(tree->queue, &obj->root);
}

bool general_tree_end(tree_obj_t *obj)
{
    general_tree_obj_t *tree = (general_tree_obj_t *)obj;

    return (queue_length(tree->queue) == 0);
}

void general_tree_next(tree_obj_t *obj)
{
    general_tree_node_t *node = NULL;
    general_tree_obj_t *tree = (general_tree_obj_t *)obj;
    bool ret = (queue_length(tree->queue) != 0);

    if (ret)
    {
        queue_front(tree->queue, &node);
        queue_remove(tree->queue);

        if (node)
        {
            for (list_begin(node->child); !list_end(node->child); list_next(node->child))
            {
                queue_add(tree->queue, list_current(node->child));
            }
        }
    }
}

tree_value_t *general_tree_current(tree_obj_t *obj)
{
    general_tree_obj_t *tree = (general_tree_obj_t *)obj;
    general_tree_node_t *node = NULL;

    if (!general_tree_end(obj))
    {
        queue_front(tree->queue, &node);

        return node->value;
    }

    return NULL;
}