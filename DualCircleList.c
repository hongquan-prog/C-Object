#include "DualCircleList.h"

typedef struct
{
    list_def base;
    struct dual_link_list_node* current;
    struct dual_link_list_node head;
} dual_circle_list_def;

static list_vtable_def s_dual_circle_list_vtable =
    {
        .insert = dual_circle_list_insert,
        .remove = dual_circle_list_remove,
        .find = link_list_find,
        .get = link_list_get,
        .set = NULL,
        .length = vector_length,
        .destroy = dual_circle_list_destroy,
        .begin = dual_link_list_begin,
        .end = dual_circle_list_end,
        .next = dual_link_list_next,
        .current = dual_link_list_current};

static DualLinkListNode dual_circle_list_position(DualCircleList *list, int position)
{
    dual_circle_list_def *obj = (dual_circle_list_def *)list;
    struct dual_link_list_node *current = (struct dual_link_list_node *)(&(obj->head));
    if (position > obj->base.length / 2)
    {
        current = current->next->pre;
        for (int i = 0; i < position; i++)
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

static void dual_circle_list_add(struct dual_link_list_node *node,
                                 struct dual_link_list_node *pre,
                                 struct dual_link_list_node *next)
{
    node->pre = pre;
    node->next = next;
    next->pre = node;
    pre->next = node;
}

bool dual_circle_push_back(DualCircleList *list, DualCircleListNode node)
{
    bool ret = false;
    dual_circle_list_def *obj = list;

    if (list && node)
    {
        if (0 == obj->base.length)
        {
            dual_circle_list_add(node, node, node);
            obj->head.next = node;
        }
        else
        {
            dual_circle_list_add(node, obj->head.next->pre, obj->head.next);
        }
        ++obj->base.length;
        ret = true;
    }
    return ret;
}

bool dual_circle_push_front(DualCircleList *list, DualCircleListNode node)
{
    bool ret = dual_circle_push_back(list, node);
    dual_circle_list_def *obj = list;
    if (ret)
    {
        obj->head.next = node;
    }
    return ret;
}

DualCircleListNode dual_circle_pop_front(DualCircleList *list)
{
    return dual_circle_list_remove(list, 0);
}

DualCircleListNode dual_circle_pop_back(DualCircleList *list)
{
    return dual_circle_list_remove(list, ((dual_circle_list_def *)list)->base.length - 1);
}

bool dual_circle_list_insert(DualCircleList *list, int i, const DualCircleListNode node)
{
    bool ret = true;
    dual_circle_list_def *obj = list;
    if (obj && (i >= 0) && (i <= obj->base.length) && node)
    {
        if (0 == obj->base.length)
        {
            dual_circle_list_add(node, node, node);
            obj->head.next = node;
        }
        else
        {
            struct dual_link_list_node *current = dual_circle_list_position(obj, i);
            dual_circle_list_add(node, current->next->pre, current->next);
        }
        ++obj->base.length;
    }
    else
    {
        ret = false;
    }
    return ret;
}

DualCircleListNode dual_circle_list_remove(DualCircleList *list, int i)
{
    DualLinkListNode ret = NULL;
    dual_circle_list_def *obj = list;
    if (obj && (i >= 0) && (i < obj->base.length))
    {
        struct dual_link_list_node *current = dual_link_list_position(obj, i);
        struct dual_link_list_node *toDel = current->next;
        struct dual_link_list_node *pre = toDel->pre;
        struct dual_link_list_node *next = toDel->next;
        if (current)
        {
            ret = toDel;
            current->next = next;
            next->pre = pre;
            --obj->base.length;
        }
    }
    return ret;
}

DualCircleList *dual_circle_list_create()
{
    dual_circle_list_def *ret = dual_link_list_create();
    if (ret)
    {
        ret->base.vtable = &s_dual_circle_list_vtable;
        ret->head.next = NULL;
        ret->head.pre = NULL;
    }
    return ret;
}

void dual_circle_list_destroy(DualCircleList *list)
{
    free(list);
}

bool dual_circle_list_end(DualLinkList *list)
{
    bool ret = false;
    if (list)
    {
        dual_circle_list_def *obj = list;
        ret = (obj->current == NULL || obj->base.length == 0);
    }
    return ret;
}