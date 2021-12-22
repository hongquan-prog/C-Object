#include "LinkList.h"

typedef struct
{
    list_def base;
    struct link_list_node* current;
    struct link_list_node head;
} link_list_def;

static list_vtable_def s_link_list_vtable =
    {
        .insert = link_list_insert,
        .remove = link_list_remove,
        .find = link_list_find,
        .get = link_list_get,
        .set = NULL,
        .length = vector_length,
        .destroy = link_list_destroy,
        .begin = link_list_begin,
        .end = link_list_end,
        .next = link_list_next,
        .current = link_list_current};

LinkListNode link_list_position(LinkList *list, int position)
{
    link_list_def *obj = (link_list_def *)list;
    struct link_list_node *current = (struct link_list_node *)(&(obj->head));
    for (int i = 0; i < position; i++)
    {
        current = current->next;
    }
    return current;
}

LinkList *link_list_create()
{
    link_list_def *list = malloc(sizeof(link_list_def));
    if (list)
    {
        list->current = NULL;
        list->base.length = 0;
        list->base.vtable = &s_link_list_vtable;
        list->head.next = NULL;
    }
    return (LinkList *)list;
}

bool link_list_insert(LinkList *list, int i, const LinkListNode node)
{
    bool ret = true;
    link_list_def *obj = (link_list_def *)list;
    if (obj && (i >= 0) && (i <= obj->base.length) && node)
    {
        struct link_list_node *current = link_list_position(obj, i);
        if (current)
        {
            ((struct link_list_node *)node)->next = current->next;
            current->next = node;
            ++obj->base.length;
        }
    }
    else
    {
        ret = false;
    }
    return ret;
}

LinkListNode link_list_remove(LinkList *list, int i)
{
    LinkListNode ret = NULL;
    link_list_def *obj = (link_list_def *)list;
    if (obj && (i >= 0) && (i < obj->base.length))
    {
        struct link_list_node *current = link_list_position(obj, i);
        struct link_list_node *next = (current) ? (current->next) : (NULL);
        if (current && next)
        {
            ret = next;
            current->next = next->next;
            --obj->base.length;
        }
    }
    return ret;
}

int link_list_find(LinkList *list, const LinkListNode node)
{
    int ret = -1;
    link_list_def *obj = (link_list_def *)list;
    if (obj && node)
    {
        struct link_list_node *current = &(obj->head);
        for (int i = 0; i < obj->base.length; i++)
        {
            current = current->next;
            if (current == node)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

bool link_list_get(LinkList *list, int i, LinkListNode *node)
{
    bool ret = true;
    link_list_def *obj = (link_list_def *)list;
    if (obj && (i >= 0) && (i < obj->base.length) && node)
    {
        struct link_list_node *current = link_list_position(obj, i);
        *((struct link_list_node **)node) = current->next;
    }
    else
    {
        ret = false;
    }
    return ret;
}

void link_list_destroy(LinkList *list)
{
    free(list);
}

void link_list_begin(LinkList *list)
{
    if (list)
    {
        ((link_list_def *)list)->current = ((link_list_def *)list)->head.next;
    }
}

void link_list_next(LinkList *list)
{
    if (list)
    {
        ((link_list_def *)list)->current = ((link_list_def *)list)->current->next;
    }
}

bool link_list_end(LinkList *list)
{
    bool ret = false;
    if (list)
    {
        ret = (((link_list_def *)list)->current == NULL);
    }
    return ret;
}

LinkListNode link_list_current(LinkList *list)
{
    return (list) ? (((link_list_def *)list)->current) : (NULL);
}