#include "dual_circle_list.h"
#include <string.h>
#include <stdlib.h>

static void dual_circle_list_destruct(list_obj_t *obj);
extern const list_obj_class_t g_dual_link_list_class;

static list_vtable_t s_dual_circle_list_vtable = {
    .insert = dual_circle_list_insert,
    .remove = dual_circle_list_remove,
    .find = dual_link_list_find,
    .get = dual_circle_list_get,
    .set = dual_circle_list_set,
    .length = NULL,
    .begin = dual_link_list_begin,
    .end = dual_circle_list_end,
    .next = dual_link_list_next,
    .pre = dual_link_list_pre,
    .current = dual_link_list_current};

const list_obj_class_t g_dual_circle_list_class = {
    .vtable = &s_dual_circle_list_vtable,
    .destructor_cb = dual_circle_list_destruct,
    .instance_size = sizeof(dual_link_list_obj_t),
    .type_name = "dual circle list"};

list_obj_t *dual_circle_list_create(int item_size)
{
    list_obj_t *obj = NULL;
    list_construct_args_t args = { 0 };

    if (item_size > 0)
    {
        /* pass args */
        args.item_size = &item_size;
        /* allocate memory and init data */
        obj = list_obj_class_create_obj(&g_dual_circle_list_class, &args);
    }

    return obj;
}

static dual_link_list_node_t *dual_circle_list_position(list_obj_t *obj, int position)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;
    dual_link_list_node_t *current = &(list->head);

    if (position > obj->list_length / 2)
    {
        current = current->next->pre;
        
        for (int i = obj->list_length; i != position; i--)
        {
            current = current->pre;
        }
    }
    else
    {
        for (int i = 0; i < position; i++)
        {
            current = current->next;
        }
    }

    return current;
}

static void dual_circle_list_add(dual_link_list_node_t *node,
                                 dual_link_list_node_t *pre,
                                 dual_link_list_node_t *next)
{
    node->pre = pre;
    node->next = next;
    next->pre = node;
    pre->next = node;
}

bool dual_circle_list_get(list_obj_t *obj, int i, list_node_t *node)
{
    bool ret = true;
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;
    
    i = (i % obj->list_length);

    if (list && node)
    {
        dual_link_list_node_t *current = dual_circle_list_position(obj, i);
        memcpy(node, current->next->user_data, obj->item_size);
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool dual_circle_list_set(list_obj_t *obj, int i, const list_node_t *node)
{
    bool ret = true;
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;
    
    i = (i % obj->list_length);

    if (list && node)
    {
        dual_link_list_node_t *current = dual_circle_list_position(obj, i);
        memcpy(current->next->user_data, node, obj->item_size);
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool dual_circle_list_push_back(list_obj_t *obj, list_node_t *node)
{
    bool ret = false;
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (list && node)
    {
        dual_link_list_node_t *item = malloc(sizeof(dual_link_list_node_t));

        if (item)
        {
            item->user_data = malloc(obj->item_size);

            if (item->user_data)
            {
                memcpy(item->user_data, node, obj->item_size);

                if (0 == obj->list_length)
                {
                    dual_circle_list_add(item, item, item);
                    list->head.next = item;
                }
                else
                {
                    dual_circle_list_add(item, list->head.next->pre, list->head.next);
                }

                obj->list_length += 1;
                ret = true;
            }
            else
            {
                free(item);
            }
        }
    }

    return ret;
}

bool dual_circle_list_push_front(list_obj_t *obj, list_node_t *node)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;
    bool ret = dual_circle_list_push_back(obj, node);

    if (ret)
    {
        list->head.next = list->head.next->pre;
    }

    return ret;
}

void dual_circle_list_pop_front(list_obj_t *obj, list_node_t * node)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if(obj->list_length)
    {
        memcpy(node, list->head.next->user_data, obj->item_size);
        dual_circle_list_remove(obj, 0);
    }
}

void dual_circle_list_pop_back(list_obj_t *obj, list_node_t * node)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if(obj->list_length)
    {
        dual_link_list_node_t *item = list->head.next;

        item = item->pre;
        memcpy(node, item->user_data, obj->item_size);
        dual_circle_list_remove(obj, obj->list_length - 1);
    }
}

bool dual_circle_list_insert(list_obj_t *obj, int i, const list_node_t * node)
{
    bool ret = false;
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (obj && (i >= 0) && (i <= obj->list_length) && node)
    {
        dual_link_list_node_t *item = malloc(sizeof(dual_link_list_node_t));

        if (item)
        {
            item->user_data = malloc(obj->item_size);

            if (item->user_data)
            {
                memcpy(item->user_data, node, obj->item_size);

                if (0 == obj->list_length)
                {
                    dual_circle_list_add(item, item, item);
                    list->head.next = item;
                }
                else
                {
                    dual_link_list_node_t *current = dual_circle_list_position(obj, i);
                    dual_circle_list_add(item, current->next->pre, current->next);
                }

                obj->list_length += 1;
                ret = true;
            }
            else
            {
                free(item);
            }
        }
    }
    else
    {
        ret = false;
    }
    return ret;
}

void dual_circle_list_remove(list_obj_t *obj, int i)
{
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (obj && (i >= 0) && (i < obj->list_length))
    {
        dual_link_list_node_t *current = dual_circle_list_position(obj, i);
        dual_link_list_node_t *toDel = current->next;
        dual_link_list_node_t *pre = toDel->pre;
        dual_link_list_node_t *next = toDel->next;

        if (current)
        {
            current->next = next;
            next->pre = pre;
            pre->next = next;
            obj->list_length -= 1;

            free(toDel->user_data);
            free(toDel);
        }
    }
}

bool dual_circle_list_end(list_obj_t *obj)
{
    bool ret = false;
    dual_link_list_obj_t *list = (dual_link_list_obj_t *)obj;

    if (list)
    {
        ret = (list->current == NULL || obj->list_length == 0);
    }
    return ret;
}

static void dual_circle_list_destruct(list_obj_t *obj)
{
    while (obj->list_length)
    {
        dual_circle_list_remove(obj, 0);
    }
}