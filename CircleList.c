#include "CircleList.h"

typedef struct
{
    list_def base;
    struct link_list_node *current;
    struct link_list_node head;
} circle_list_def;

static list_vtable_def s_circle_list_vtable =
    {
        .insert = circle_list_insert,
        .remove = circle_list_remove,
        .find = link_list_find,
        .get = circle_list_get,
        .set = NULL,
        .length = vector_length,
        .destroy = circle_list_destroy,
        .begin = circle_list_begin,
        .end = circle_list_end,
        .next = circle_list_next,
        .current = circle_list_current};

static void last_to_first(circle_list_def *list)
{
    struct link_list_node *ret = link_list_position(list, list->base.length - 1);
    if (ret)
    {
        ret->next->next = list->head.next;
    }
}

CircleList *circle_list_create()
{
    circle_list_def *list = link_list_create();
    if (list)
    {
        list->base.vtable = &s_circle_list_vtable;
    }
    return list;
}

bool circle_list_insert(CircleList *list, int i, const CircleListNode node)
{
    bool ret = true;

    circle_list_def *obj = (circle_list_def *)list;
    i = (i % (obj->base.length + 1));
    ret = link_list_insert(list, i, node);
    if (ret && (i == 0))
    {
        last_to_first(obj);
    }

    
    return ret;
}

CircleListNode circle_list_remove(CircleList *list, int i)
{
    CircleListNode ret = NULL;
    circle_list_def *obj = (circle_list_def *)list;
    i = (i % obj->base.length);
    if (i == 0)
    {
        struct link_list_node *toDel = obj->head.next;
        ret = toDel;
        obj->base.length--;
        obj->head.next = (obj->base.length != 0) ? (toDel->next) : (NULL);
        if (obj->base.length != 0)
        {
            last_to_first(obj);
        }
    }
    else
    {
        ret = link_list_remove(list, i);
    }
    return ret;
}

bool circle_list_get(CircleList *list, int i, CircleListNode *node)
{
    circle_list_def *obj = (circle_list_def *)list;
    i = (i % obj->base.length);
    return link_list_get(list, i, node);
}

void circle_list_destroy(CircleList *list)
{
    link_list_destroy(list);
}

void circle_list_begin(CircleList *list)
{
    if (list)
    {
        ((circle_list_def *)list)->current = ((circle_list_def *)list)->head.next;
    }
}

void circle_list_next(CircleList *list)
{
    if (list)
    {
        ((circle_list_def *)list)->current = ((circle_list_def *)list)->current->next;
    }
}

bool circle_list_end(CircleList *list)
{
    bool ret = false;
    if (list)
    {
        circle_list_def *obj = list;
        ret = (obj->current == NULL || obj->base.length == 0);
    }
    return ret;
}

CircleListNode circle_list_current(CircleList *list)
{
    return (list) ? (((circle_list_def *)list)->current) : (NULL);
}