#ifndef DUAL_CIRCLE_LIST_H
#define DUAL_CIRCLE_LIST_H

#include "DualLinkList.h"

typedef void DualCircleList;
typedef void *DualCircleListNode;

DualCircleList *dual_circle_list_create();
void dual_circle_list_destroy(DualCircleList *list);
bool dual_circle_push_back(DualCircleList *list, DualCircleListNode node);
bool dual_circle_push_front(DualCircleList *list, DualCircleListNode node);
DualCircleListNode dual_circle_pop_front(DualCircleList *list);
DualCircleListNode dual_circle_pop_back(DualCircleList *list);
bool dual_circle_list_insert(DualCircleList *list, int i, const DualCircleListNode node);
DualCircleListNode dual_circle_list_remove(DualCircleList *list, int i);

bool dual_circle_list_end(DualCircleList *list);

#endif