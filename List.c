#include "List.h"

void list_insert(List *list, int i, ListNode node)
{
    if ((*((list_vtable_def **)list))->insert)
    {
        (*((list_vtable_def **)list))->insert(list, i, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "insert function not exist in vtable");
    }
}

ListNode list_remove(List *list, int i)
{
    ListNode ret = NULL;
    if ((*((list_vtable_def **)list))->remove)
    {
        ret = (*((list_vtable_def **)list))->remove(list, i);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "remove function not exist in vtable");
    }
    return ret;
}

ListNode list_get(List *list, int i)
{
    ListNode ret = NULL;
    if ((*((list_vtable_def **)list))->get)
    {
        (*((list_vtable_def **)list))->get(list, i, &ret);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "get function not exist in vtable");
    }
    return ret;
}

bool list_set(List *list, int i, const ListNode node)
{
    if ((*((list_vtable_def **)list))->set)
    {
        return (*((list_vtable_def **)list))->set(list, i, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "set function not exist in vtable");
        return false;
    }
}

int list_length(List *list)
{
    if ((*((list_vtable_def **)list))->length)
    {
        return (*((list_vtable_def **)list))->length(list);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "length function not exist in vtable");
        return 0;
    }
}

int list_find(List *list, const ListNode node)
{
    if ((*((list_vtable_def **)list))->find)
    {
        return (*((list_vtable_def **)list))->find(list, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "find function not exist in vtable");
        return -1;
    }
}

void list_begin(List *list)
{
    if ((*((list_vtable_def **)list))->begin)
    {
        (*((list_vtable_def **)list))->begin(list);
    }
}

void list_next(List *list)
{
    if ((*((list_vtable_def **)list))->next)
    {
        (*((list_vtable_def **)list))->next(list);
    }
}

bool list_end(List *list)
{
    bool ret = true;
    if ((*((list_vtable_def **)list))->end)
    {
        ret = (*((list_vtable_def **)list))->end(list);
    }
    return ret;
}

ListNode list_current(List *list)
{
    ListNode ret = NULL;
    if ((*((list_vtable_def **)list))->current)
    {
        ret = (*((list_vtable_def **)list))->current(list);
    }
    return ret;
}

void list_destory(List *list)
{
    if((*((list_vtable_def **)list))->destroy)
    {
        (*((list_vtable_def **)list))->destroy(list);
    }
}