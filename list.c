#include "list.h"
#include <stdlib.h>
#include <string.h>

static void list_obj_construct(list_obj_t *obj, int item_size);
static void list_obj_destruct(list_obj_t *obj);

list_obj_t *list_obj_class_create_obj(const list_obj_class_t *class_p, int item_size)
{
    uint32_t s = class_p->instance_size;
    list_obj_t *obj = malloc(s);

    if (obj == NULL)
    {
        return NULL;
    }

    memset(obj, 0, s);
    obj->class_p = class_p;
    list_obj_construct(obj, item_size);

    return obj;
}

list_obj_t *list_delete(list_obj_t *obj)
{
    list_obj_destruct(obj);
    free(obj);
}

/*-----------------
 * interface
 *----------------*/

void list_insert(list_obj_t *list, int i, const list_node_t *node)
{
    if (list->class_p->vtable->insert)
    {
        list->class_p->vtable->insert(list, i, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "insert function not exist in vtable");
    }
}

void list_remove(list_obj_t *list, int i)
{
    if (list->class_p->vtable->remove)
    {
        list->class_p->vtable->remove(list, i);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "remove function not exist in vtable");
    }
}

bool list_get(list_obj_t *list, int i, list_node_t *node)
{
    bool ret = false;

    if (list->class_p->vtable->get)
    {
        return list->class_p->vtable->get(list, i, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "get function not exist in vtable");
    }
    return ret;
}

bool list_set(list_obj_t *list, int i, const list_node_t *node)
{
    if (list->class_p->vtable->set)
    {
        return list->class_p->vtable->set(list, i, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "set function not exist in vtable");
        return false;
    }
}

int list_length(list_obj_t *list)
{
    if (list->class_p->vtable->length)
    {
        return list->class_p->vtable->length(list);
    }
    else
    {
        return list->list_length;
    }
}

int list_find(list_obj_t *list, const list_node_t *node)
{
    if (list->class_p->vtable->find)
    {
        return list->class_p->vtable->find(list, node);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "find function not exist in vtable");
        return -1;
    }
}

void list_begin(list_obj_t *list)
{
    if (list->class_p->vtable->begin)
    {
        list->class_p->vtable->begin(list);
    }
}

void list_next(list_obj_t *list)
{
    if (list->class_p->vtable->next)
    {
        list->class_p->vtable->next(list);
    }
}

void list_pre(list_obj_t *list)
{
    if (list->class_p->vtable->next)
    {
        list->class_p->vtable->pre(list);
    }
}

bool list_end(list_obj_t *list)
{
    bool ret = true;
    if (list->class_p->vtable->end)
    {
        ret = list->class_p->vtable->end(list);
    }
    return ret;
}

list_node_t *list_current(list_obj_t *list)
{
    list_node_t *ret = NULL;
    if (list->class_p->vtable->current)
    {
        ret = list->class_p->vtable->current(list);
    }
    return ret;
}

/*-----------------
 * static function
 *----------------*/

static void list_obj_construct(list_obj_t *obj, int item_size)
{
    const list_obj_class_t *original_class_p = obj->class_p;

    if (obj->class_p->base_class)
    {
        /*Don't let the descendant methods run during constructing the ancestor type*/
        obj->class_p = obj->class_p->base_class;

        /*Construct the base first*/
        list_obj_construct(obj, item_size);
    }

    /*Restore the original class*/
    obj->class_p = original_class_p;
    obj->item_size = item_size;

    if (obj->class_p->constructor_cb)
    {
        obj->class_p->constructor_cb(obj, item_size);
    }
}

static void list_obj_destruct(list_obj_t *obj)
{
    if (obj->class_p->destructor_cb)
    {
        obj->class_p->destructor_cb(obj);
    }

    if (obj->class_p->base_class)
    {
        /*Don't let the descendant methods run during destructing the ancestor type*/
        obj->class_p = obj->class_p->base_class;

        /*Call the base class's destructor too*/
        list_obj_destruct(obj);
    }
}