#include "link_list.h"
#include <string.h>
#include <stdlib.h>

extern const obj_class_t g_list_class;
static void link_list_constructor(obj_t *obj, obj_constructor_args_t *args);
static void link_list_destructor(obj_t *obj);

const static list_vtable_t s_link_list_vtable = {
    .insert = link_list_insert,
    .remove = link_list_remove,
    .find = link_list_find,
    .get = link_list_get,
    .set = link_list_set,
    .clear = link_list_clear,
    .length = NULL,
    .begin = link_list_begin,
    .end = link_list_end,
    .next = link_list_next,
    .pre = NULL,
    .current = link_list_current};

const obj_class_t g_link_list_class = {
    .vtable = (obj_vtable_t *)&s_link_list_vtable,
    .base_class = &g_list_class,
    .constructor_cb = link_list_constructor,
    .destructor_cb = link_list_destructor,
    .instance_size = sizeof(link_list_obj_t),
    .class_name = "link list"};

list_obj_t *link_list_create(int item_size)
{
    list_obj_t *obj = NULL;
    list_constructor_args_t args = {0};

    if (item_size > 0)
    {
        /* pass args */
        args.item_size = &item_size;
        /* allocate memory and init data */
        obj = (list_obj_t *)obj_class_create_obj(&g_link_list_class, (obj_constructor_args_t *)&args);
    }

    return obj;
}

link_list_node_t *link_list_position(link_list_obj_t *list, int position)
{
    link_list_node_t *current = &(list->head);

    for (int i = 0; i < position; i++)
    {
        current = current->next;
    }

    return current;
}

bool link_list_insert(list_obj_t *obj, int i, const list_node_t *node)
{
    bool ret = true;
    link_list_obj_t *list = (link_list_obj_t *)obj;

    if (obj && (i >= 0) && (i <= obj->list_length) && node)
    {
        link_list_node_t *current = link_list_position(list, i);

        if (current)
        {
            link_list_node_t *item = malloc(sizeof(link_list_node_t));

            if (item)
            {
                item->user_data = malloc(obj->item_size);

                if (!item->user_data)
                {
                    free(item);
                    ret = false;
                }
                else
                {
                    memcpy(item->user_data, node, obj->item_size);
                    item->next = current->next;
                    current->next = item;
                    obj->list_length += 1;
                }
            }
            else
            {
                ret = false;
            }
        }
        else
        {
            ret = false;
        }
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool link_list_append(list_obj_t *obj, const list_node_t *node)
{
    return link_list_insert(obj, obj->list_length, node);
}

void link_list_remove(list_obj_t *obj, int i)
{
    link_list_obj_t *list = (link_list_obj_t *)obj;

    if (list && (i >= 0) && (i < obj->list_length))
    {
        link_list_node_t *current = link_list_position(list, i);
        link_list_node_t *next = (current) ? (current->next) : (NULL);

        if (current && next)
        {
            current->next = next->next;
            obj->list_length -= 1;
            free(next->user_data);
            free(next);
        }
    }
}

int link_list_find(list_obj_t *obj, const list_node_t *node)
{
    int ret = -1;
    link_list_obj_t *list = (link_list_obj_t *)obj;

    if (obj && node)
    {
        link_list_node_t *current = &(list->head);

        for (int i = 0; i < obj->list_length; i++)
        {
            current = current->next;

            if (obj->equal)
            {
                if (obj->equal(current->user_data, node))
                {
                    ret = i;
                    break;
                }
            }
            else if (0 == memcmp(current->user_data, node, obj->item_size))
            {
                ret = i;
                break;
            }
        }
    }

    return ret;
}

bool link_list_get(list_obj_t *obj, int i, list_node_t *node)
{
    bool ret = true;
    link_list_obj_t *list = (link_list_obj_t *)obj;

    if (obj && (i >= 0) && (i < obj->list_length) && node)
    {
        link_list_node_t *current = link_list_position(list, i);
        memcpy(node, current->next->user_data, obj->item_size);
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool link_list_set(list_obj_t *obj, int i, const list_node_t *node)
{
    bool ret = true;
    link_list_obj_t *list = (link_list_obj_t *)obj;

    if (obj && (i >= 0) && (i < obj->list_length) && node)
    {
        link_list_node_t *current = link_list_position(list, i);
        memcpy(current->next->user_data, node, obj->item_size);
    }
    else
    {
        ret = false;
    }

    return ret;
}

void link_list_clear(list_obj_t *obj)
{
    while (obj->list_length)
    {
        link_list_remove(obj, 0);
    }
}

void link_list_begin(list_obj_t *obj)
{
    link_list_obj_t *list = (link_list_obj_t *)obj;

    if (list)
    {
        list->current = list->head.next;
    }
}

void link_list_next(list_obj_t *obj)
{
    link_list_obj_t *list = (link_list_obj_t *)obj;

    if (list)
    {
        list->current = list->current->next;
    }
}

bool link_list_end(list_obj_t *obj)
{
    bool ret = false;
    link_list_obj_t *list = (link_list_obj_t *)obj;

    if (list)
    {
        ret = (NULL == list->current);
    }
    return ret;
}

list_node_t *link_list_current(list_obj_t *obj)
{
    link_list_obj_t *list = (link_list_obj_t *)obj;

    return (list) ? (list->current->user_data) : (NULL);
}

static void link_list_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    if (obj)
    {
        link_list_obj_t *list = (link_list_obj_t *)obj;

        list->current = NULL;
        list->head.next = NULL;
        list->head.user_data = NULL;
    }
}

static void link_list_destructor(obj_t *obj)
{
    if (obj)
    {
        link_list_clear((list_obj_t *)obj);
    }
}