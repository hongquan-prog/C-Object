#include "Vector.h"

static vector_vtable s_vector_vtable = {
    .insert = vector_insert,
    .remove = vector_remove,
    .find = vector_find,
    .get = vector_get,
    .set = vector_set,
    .length = vector_length
};

Vector* vector_create(int length)
{
    vector_def* ret = NULL;

    if(length > 0)
    {
        ret = malloc(sizeof(vector_def));
        ret->head = malloc(sizeof(VectorNode) * length);
        if(ret && ret->head)
        {
            ret->vtable = &s_vector_vtable;
            ret->length = length;
            for(int i = 0; i < length; i++)
            {
                ret->head[i] = NULL;
            }
        }
    }
    return (Vector*)ret;
}

bool vector_insert(Vector* list, int i, const VectorNode node)
{
    bool ret = true;
    vector_def* obj = (vector_def*)list;

    if(obj && (i >= 0) && (i < obj->length) && node)
    {
        for(int j = obj->length - 1; j > i; j--)
        {
            obj->head[j] = obj->head[j - 1];
        }
        obj->head[i] = node;
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool vector_remove(Vector* list, int i)
{
    bool ret = true;
    vector_def* obj = (vector_def*)list;

    if(obj && (i >= 0) && (i < obj->length))
    {
        for(int j = i + 1; j < obj->length; j++)
        {
            obj->head[j - 1] = obj->head[j];
        }
    }
    else
    {
        ret = false;
    }
    return ret;
}

int vector_find(Vector* list, const VectorNode node)
{
    int ret = -1;
    vector_def* obj = (vector_def*)list;

    if(obj && node)
    {
        for(int i = 0; i < obj->length; i++)
        {
            if(obj->head[i] == node)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

bool vector_get(Vector* list, int i, VectorNode* node)
{
    bool ret = true;
    vector_def* obj = (vector_def*)list;

    if(obj && (i >= 0) && (i < obj->length) && node)
    {
        *node = obj->head[i];
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool vector_set(Vector* list, int i, const VectorNode node)
{
    bool ret = true;
    vector_def* obj = (vector_def*)list;

    if(obj && (i >= 0) && (i < obj->length) && node)
    {
        obj->head[i] = node;
    }
    else
    {
        ret = false;
    }
    return ret;
}

int vector_length(Vector* list)
{
    int ret = 0;

    ret = (list) ? ((vector_def*)list)->length : (0);

    return ret;
}

void vector_clear(Vector* list)
{
    if(list)
    {
        free(((vector_def*)list)->head);
        free(list);
    }
}