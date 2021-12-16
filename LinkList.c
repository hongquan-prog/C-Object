#include "LinkList.h"

typedef struct
{
    vector_def base;
    struct link_list_node head;
}link_list_def;

static vector_vtable s_link_list_vtable = 
{
    .insert = link_list_insert,
    .remove = link_list_remove,
    .find = link_list_find,
    .get = link_list_get,
    .set = link_list_set,
    .length = vector_length
};


static struct link_list_node * position(link_list_def* list,int position)
{
    struct link_list_node* current = (struct link_list_node*)(&(list->head));
    for(int i = 0; i < position; i++)
    {
        current = current->next;
    }
    return current; 
}

#include <stdio.h>

LinkList* link_list_create()
{
    link_list_def* list = malloc(sizeof(link_list_def));
    if(list)
    {
        list->base.length = 0;
        list->base.head = NULL;
        list->base.vtable = &s_link_list_vtable;
        list->head.next = NULL;
    }
    return (LinkList*)list;
}

bool link_list_insert(LinkList* list, int i, const LinkListNode node)
{
    bool ret = true;
    link_list_def* obj = (link_list_def*)list;
    if(obj && (i >= 0) && (i <= obj->base.length) && node)
    {
        struct link_list_node* current = position(obj, i);
        if(current)
        {
            ((struct link_list_node*)node)->next = current->next;
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

bool link_list_remove(LinkList* list, int i)
{
    bool ret = true;
    link_list_def* obj = (link_list_def*)list;
    if(obj && (i >= 0) && (i < obj->base.length))
    {
        struct link_list_node* current = position(obj, i);
        struct link_list_node* next = current->next;
        if(current)
        {
            current->next = next->next;
            --obj->base.length;
        }        
    }
    else
    {
        ret = false;
    }
    return ret;
}

int link_list_find(LinkList* list, const LinkListNode node)
{
    int ret = -1;
    link_list_def* obj = (link_list_def*)list;
    if(obj && node)
    {
        struct link_list_node* current = &(obj->head);
        for(int i = 0; i < obj->base.length; i++)
        {
            current = current->next;
            if(current == node)
            {
                ret = i;
                break;
            }
        }    
    }
    return ret;
}

bool link_list_get(LinkList* list, int i, LinkListNode* node)
{
    bool ret = true;
    link_list_def* obj = (link_list_def*)list;
    if(obj && (i >= 0) && (i < obj->base.length) && node)
    {
        struct link_list_node* current = position(obj, i);
        *((struct link_list_node**)node) = current->next;
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool link_list_set(LinkList* list, int i, const LinkListNode node)
{
    bool ret = true;
    link_list_def* obj = (link_list_def*)list;
    if(obj && (i >= 0) && (i < obj->base.length) && node)
    {
        struct link_list_node* current = position(obj, i);
        ((struct link_list_node*)node)->next = current->next; 
        current->next = node;
    }
    else
    {
        ret = false;
    }
    return ret;
}

void link_list_clear(LinkList* list)
{
    free(list);
}
