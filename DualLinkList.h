#ifndef DUAL_LINK_LIST_H
#define DUAL_LINK_LIST_H

#include "LinkList.h"

typedef void DualLinkList;
typedef void *DualLinkListNode;

struct dual_link_list_node
{
    struct dual_link_list_node *next;
    struct dual_link_list_node *pre;
};

DualLinkList *dual_link_list_create();
bool dual_link_list_insert(DualLinkList *list, int i, const DualLinkListNode node);
DualLinkListNode dual_link_list_remove(DualLinkList *list, int i);
int dual_link_list_find(DualLinkList *list, const DualLinkListNode node);
bool dual_link_list_get(DualLinkList *list, int i, DualLinkListNode *node);
void dual_link_list_destroy(DualLinkList *list);
DualLinkListNode dual_link_list_position(DualLinkList *list, int position);

void dual_link_list_begin(DualLinkList *list);
void dual_link_list_next(DualLinkList *list);
bool dual_link_list_end(DualLinkList *list);
DualLinkListNode dual_link_list_current(DualLinkList *list);

#endif