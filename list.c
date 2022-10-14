#include "list.h"
#include <stdlib.h>

static void list_constructor(obj_t *obj, obj_constructor_args_t *args);

const obj_class_t g_list_class = {
    .vtable = NULL,
    .base_class = NULL,
    .constructor_cb = list_constructor,
    .destructor_cb = NULL,
    .instance_size = sizeof(list_obj_t),
    .class_name = "list" };

static void list_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    list_constructor_args_t *list_args = (list_constructor_args_t *)args;

    if (obj)
    {
        list_obj_t *ret = (list_obj_t *)obj;
        ret->item_size = *(list_args->item_size);
        ret->list_length = 0;
    }
}

/*--------------------------------------------------------------
 * interface
 *------------------------------------------------------------*/

void list_delete(list_obj_t *obj)
{
    obj_class_delete_obj((obj_t *)obj);
}

void list_insert(list_obj_t *list, int i, const list_node_t *node)
{
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->insert)
    {
        vtable->insert(list, i, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "insert function not exist in vtable");
    }
}

void list_remove(list_obj_t *list, int i)
{
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->remove)
    {
        vtable->remove(list, i);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "remove function not exist in vtable");
    }
}

bool list_get(list_obj_t *list, int i, list_node_t *node)
{
    bool ret = false;
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;

    if (vtable->get)
    {
        return vtable->get(list, i, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "get function not exist in vtable");
    }
    return ret;
}

bool list_set(list_obj_t *list, int i, const list_node_t *node)
{
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->set)
    {
        return vtable->set(list, i, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "set function not exist in vtable");
        return false;
    }
}

int list_length(list_obj_t *list)
{
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->length)
    {
        return vtable->length(list);
    }
    else
    {
        return list->list_length;
    }
}

int list_find(list_obj_t *list, const list_node_t *node)
{
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->find)
    {
        return vtable->find(list, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "find function not exist in vtable");
        return -1;
    }
}

void list_begin(list_obj_t *list)
{
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->begin)
    {
        vtable->begin(list);
    }
}

void list_next(list_obj_t *list)
{
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->next)
    {
        vtable->next(list);
    }
}

void list_pre(list_obj_t *list)
{
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->next)
    {
        vtable->pre(list);
    }
}

bool list_end(list_obj_t *list)
{
    bool ret = true;
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->end)
    {
        ret = vtable->end(list);
    }
    return ret;
}

list_node_t *list_current(list_obj_t *list)
{
    list_node_t *ret = NULL;
    list_vtable_t *vtable = (list_vtable_t *)list->base.class->vtable;
    
    if (vtable->current)
    {
        ret = vtable->current(list);
    }
    return ret;
}
