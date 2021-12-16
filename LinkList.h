#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "Vector.h"

struct link_list_node
{
    struct link_list_node* next;
};

typedef void LinkList;
typedef void* LinkListNode;

LinkList* link_list_create();
bool link_list_insert(LinkList* list, int i, const LinkListNode node);
bool link_list_remove(LinkList* list, int i);
int link_list_find(LinkList* list, const LinkListNode node);
bool link_list_get(LinkList* list, int i, LinkListNode* node);
bool link_list_set(LinkList* list, int i, const LinkListNode node);
void link_list_clear(LinkList* list);

#endif