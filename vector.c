#include "vector.h"
#include <string.h>
#include <stdlib.h>

static void vector_destruct(list_obj_t *obj);

const static list_vtable_t s_vector_vtable = {
    .insert = vector_insert,
    .remove = vector_remove,
    .find = vector_find,
    .get = vector_get,
    .set = vector_set,
    .length = NULL,
    .begin = vector_begin,
    .end = vector_end,
    .next = vector_next,
    .pre = NULL,
    .current = vector_current};

const list_obj_class_t g_vector_class = {
    .vtable = &s_vector_vtable,
    .destructor_cb = vector_destruct,
    .instance_size = sizeof(vector_obj_t),
    .type_name = "vector"};

list_obj_t *vector_create(int item_size, int length)
{
    list_obj_t *obj = NULL;

    if ((length > 0) && (item_size > 0))
    {
        obj = list_obj_class_create_obj(&g_vector_class, item_size);

        if (obj)
        {
            vector_obj_t *ret = (vector_obj_t *)obj;
            ret->array_length = length;
            ret->array = malloc(item_size * length);

            if (ret->array)
            {
                ret->current = NULL;
            }
            else
            {
                free(obj);
                obj = NULL;
            }
        }
    }

    return obj;
}

bool vector_insert(list_obj_t *obj, int i, const list_node_t *node)
{
    bool ret = true;
    vector_obj_t *list = (vector_obj_t *)obj;

    if (obj && (i >= 0) && (i <= obj->list_length) && (obj->list_length < list->array_length) && node)
    {
        char *dest = list->array + (obj->item_size * obj->list_length);

        if (i != obj->list_length)
        {
            for (int j = obj->list_length; j > i; j--)
            {
                memcpy(dest, dest - obj->item_size, obj->item_size);
                dest = dest - obj->item_size;
            }
        }

        obj->list_length += 1;
        memcpy(dest, node, obj->item_size);
    }
    else
    {
        ret = false;
    }

    return ret;
}

void vector_remove(list_obj_t *obj, int i)
{
    vector_obj_t *list = (vector_obj_t *)obj;

    if (obj && (i >= 0) && (i < obj->list_length))
    {
        char *dest = list->array + (obj->item_size * i);

        if (i != (obj->list_length - 1))
        {
            for (int j = i + 1; j < obj->list_length; j++)
            {
                memcpy(dest, dest + obj->item_size, obj->item_size);
                dest = dest + obj->item_size;
            }
        }

        obj->list_length -= 1;
    }
}

int vector_find(list_obj_t *obj, const list_node_t *node)
{
    int ret = -1;
    vector_obj_t *list = (vector_obj_t *)obj;

    if (obj && node)
    {
        for (int i = 0; i < obj->list_length; i++)
        {
            if (memcmp(list->array + obj->item_size * i, node, obj->item_size) == 0)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

bool vector_get(list_obj_t *obj, int i, list_node_t *node)
{
    bool ret = true;
    vector_obj_t *list = (vector_obj_t *)obj;

    if (obj && (i >= 0) && (i < obj->list_length) && node)
    {
        memcpy(node, list->array + obj->item_size * i, obj->item_size);
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool vector_set(list_obj_t *obj, int i, const list_node_t *node)
{
    bool ret = true;
    vector_obj_t *list = (vector_obj_t *)obj;

    if (obj && (i >= 0) && (i < obj->list_length) && node)
    {
        memcpy(list->array + obj->item_size * i, node, obj->item_size);
    }
    else
    {
        ret = false;
    }
    return ret;
}

void vector_begin(list_obj_t *obj)
{
    vector_obj_t *list = (vector_obj_t *)obj;

    if (obj)
    {
        list->current = list->array;
    }
}

void vector_next(list_obj_t *obj)
{
    vector_obj_t *list = (vector_obj_t *)obj;

    if (obj)
    {
        list->current = list->current + obj->item_size;
    }
}

bool vector_end(list_obj_t *obj)
{
    bool ret = false;
    vector_obj_t *list = (vector_obj_t *)obj;

    if (obj)
    {
        ret = (list->current == (list->array + (obj->list_length * obj->item_size)));
    }

    return ret;
}

list_node_t *vector_current(list_obj_t *obj)
{
    return (obj) ? (((vector_obj_t *)obj)->current) : (NULL);
}

static void vector_destruct(list_obj_t *obj)
{
    vector_obj_t *list = (vector_obj_t *)obj;

    if (list && list->array)
    {
        free(list->array);
    }
}