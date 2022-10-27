#include "circle_list.h"
#include <stdlib.h>

static void last_to_first(list_obj_t *obj);
static void circle_list_destructor(obj_t *obj);

extern const obj_class_t g_link_list_class;
extern link_list_node_t *link_list_position(link_list_obj_t *obj, int position);

static list_vtable_t s_circle_list_vtable = {
        .insert = circle_list_insert,
        .remove = circle_list_remove,
        .find = link_list_find,
        .get = circle_list_get,
        .set = circle_list_set,
        .clear = circle_list_clear,
        .length = NULL,
        .begin = link_list_begin,
        .end = circle_list_end,
        .next = link_list_next,
        .pre = NULL,
        .current = link_list_current};

const obj_class_t g_circle_list_class = {
    .vtable = (obj_vtable_t *)&s_circle_list_vtable,
    .base_class = &g_link_list_class,
    .constructor_cb = NULL,
    .destructor_cb = circle_list_destructor,
    .instance_size = sizeof(circle_list_obj_t),
    .class_name = "circle list"};

list_obj_t *circle_list_create(int item_size)
{
    list_obj_t *obj = NULL;
    list_constructor_args_t args = { 0 };

    if (item_size > 0)
    {
        /* pass args */
        args.item_size = &item_size;
        /* allocate memory and init data */
        obj = (list_obj_t *)obj_class_create_obj(&g_circle_list_class, (obj_constructor_args_t *)&args);
    }

    return obj;
}

bool circle_list_insert(list_obj_t *obj, int i, const list_node_t *node)
{
    bool ret = true;
    
    i = (i % (obj->list_length + 1));
    ret = link_list_insert(obj, i, node);

    if (ret && (0 == i))
    {
        last_to_first(obj);
    }

    return ret;
}

void circle_list_remove(list_obj_t *obj, int i)
{
    link_list_obj_t *list = (link_list_obj_t *)obj;

    i = (i % obj->list_length);

    if (0 == i)
    {
        link_list_node_t *toDel = list->head.next;

        obj->list_length--;
        list->head.next = (obj->list_length != 0) ? (toDel->next) : (NULL);

        if (obj->list_length != 0)
        {
            last_to_first(obj);
        }

        free(toDel->user_data);
        free(toDel);
    }
    else
    {
        link_list_remove(obj, i);
    }
}

bool circle_list_get(list_obj_t *obj, int i, list_node_t *node)
{
    i = (i % obj->list_length);
    
    return link_list_get(obj, i, node);
}

bool circle_list_set(list_obj_t *obj, int i, const list_node_t *node)
{
    i = (i % obj->list_length);
    
    return link_list_set(obj, i, node);
}

void circle_list_clear(list_obj_t *obj)
{
    while (obj->list_length)
    {
        circle_list_remove(obj, 0);
    }
}

bool circle_list_end(list_obj_t *obj)
{
    bool ret = false;
    link_list_obj_t *list = (link_list_obj_t *)obj;

    if (obj)
    {
        ret = ((NULL == list->current) || (0 == obj->list_length));
    }

    return ret;
}

static void last_to_first(list_obj_t *obj)
{
    link_list_obj_t *list = (link_list_obj_t *)obj;
    link_list_node_t *ret = link_list_position(list, obj->list_length - 1);

    if (ret)
    {
        ret->next->next = list->head.next;
    }
}

static void circle_list_destructor(obj_t *obj)
{
    list_obj_t *list = (list_obj_t *)obj;

    circle_list_clear(list);
}