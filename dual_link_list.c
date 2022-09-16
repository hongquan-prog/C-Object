#include "dual_link_list.h"
#include <string.h>
#include <stdlib.h>

static void dual_link_list_construct(list_obj_t *obj, int item_size);
static void dual_link_list_destruct(list_obj_t *obj);

const static list_vtable_t s_dual_link_list_vtable = {
    .insert = dual_link_list_insert,
    .remove = dual_link_list_remove,
    .find = dual_link_list_find,
    .get = dual_link_list_get,
    .set = NULL,
    .length = NULL,
    .begin = dual_link_list_begin,
    .end = dual_link_list_end,
    .next = dual_link_list_next,
    .pre = dual_link_list_pre,
    .current = dual_link_list_current};

const list_obj_class_t g_dual_link_list_class = {
    .vtable = &s_dual_link_list_vtable,
    .destructor_cb = dual_link_list_destruct,
    .instance_size = sizeof(dual_link_list_obj_t),
    .type_name = "dual link list"};

list_obj_t *dual_link_list_create(int item_size)
{
    list_obj_t *obj = NULL;

    if (item_size > 0)
    {
        obj = list_obj_class_create_obj(&g_dual_link_list_class, item_size);
    }

    return obj;
}

list_node_t *dual_link_list_position(list_obj_t *obj, int position)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;
    dual_link_list_node_t *current = &(list->head);

    for (int i = 0; i < position; i++)
    {
        current = current->next;
    }

    return current;
}

bool dual_link_list_insert(list_obj_t *obj, int i, const list_node_t *node)
{
    bool ret = false;
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (obj && (i >= 0) && (i <= obj->list_length) && node)
    {
        dual_link_list_node_t *current = dual_link_list_position(obj, i);

        if (current)
        {
            dual_link_list_node_t *item = malloc(sizeof(dual_link_list_node_t));

            if (item)
            {
                item->user_data = malloc(obj->item_size);

                if (item->user_data)
                {
                    ret = true;
                    memcpy(item->user_data, node, obj->item_size);
                    dual_link_list_node_t *next = current->next;

                    item->next = current->next;
                    item->pre = (current == &(list->head)) ? (NULL) : (current);
                    current->next = item;
                    obj->list_length += 1;
                    
                    if (next)
                    {
                        next->pre = item;
                    }
                }
                else
                {
                    free(item);
                }
            }
        }
    }

    return ret;
}

void dual_link_list_remove(list_obj_t *obj, int i)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (obj && (i >= 0) && (i < obj->list_length))
    {
        dual_link_list_node_t *current = dual_link_list_position(obj, i);
        dual_link_list_node_t *toDel = (current) ? (current->next) : (NULL);
        dual_link_list_node_t *next = (toDel) ? (toDel->next) : (NULL);

        if (toDel)
        {
            current->next = next;
            obj->list_length -= 1;

            if (next)
            {
                next->pre = toDel->pre;
            }

            free(toDel->user_data);
            free(toDel);
        }
    }
}

int dual_link_list_find(list_obj_t *obj, const list_node_t *node)
{
    int ret = -1;
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (obj && node)
    {
        dual_link_list_node_t *current = &(list->head);

        for (int i = 0; i < obj->list_length; i++)
        {
            current = current->next;

            if (0 == memcmp(current->user_data, node, obj->item_size))
            {
                ret = i;
                break;
            }
        }
    }

    return ret;
}

bool dual_link_list_get(list_obj_t *obj, int i, list_node_t *node)
{
    bool ret = true;
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (obj && (i >= 0) && (i < obj->list_length) && node)
    {
        dual_link_list_node_t *current = dual_link_list_position(obj, i);
        memcpy(node, current->next->user_data, obj->item_size);
    }
    else
    {
        ret = false;
    }

    return ret;
}

void dual_link_list_begin(list_obj_t *obj)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (list)
    {
        list->current = list->head.next;
    }
}

void dual_link_list_next(list_obj_t *obj)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (list)
    {
        list->current = list->current->next;
    }
}

void dual_link_list_pre(list_obj_t *obj)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (list)
    {
        list->current = list->current->pre;
    }
}

bool dual_link_list_end(list_obj_t *obj)
{
    bool ret = false;
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (list)
    {
        ret = (list->current == NULL);
    }

    return ret;
}

list_node_t *dual_link_list_current(list_obj_t *obj)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    return (obj) ? (list->current->user_data) : (NULL);
}

static void dual_link_list_destruct(list_obj_t *obj)
{
    while (obj->list_length)
    {
        dual_link_list_remove(obj, 0);
    }
}