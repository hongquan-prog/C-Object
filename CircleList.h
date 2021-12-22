#ifndef CIRCLE_LIST_H
#define CIRCLE_LIST_H

#include "LinkList.h"

typedef void *CircleListNode;
typedef void CircleList;

CircleList *circle_list_create();
bool circle_list_insert(CircleList *list, int i, const CircleListNode node);
CircleListNode circle_list_remove(CircleList *list, int i);
bool circle_list_get(CircleList *list, int i, CircleListNode *node);
void circle_list_destroy(CircleList *list);

void circle_list_begin(CircleList *list);
void circle_list_next(CircleList *list);
bool circle_list_end(CircleList *list);
CircleListNode circle_list_current(CircleList *list);

#endif