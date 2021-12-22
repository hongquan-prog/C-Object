#include "Vector.h"

typedef struct
{
    list_def base;
    VectorNode *current;
    VectorNode *head;
} vector_def;

static list_vtable_def s_vector_vtable = {
    .insert = vector_insert,
    .remove = vector_remove,
    .find = vector_find,
    .get = vector_get,
    .set = vector_set,
    .length = vector_length,
    .destroy = vector_destroy,
    .begin = vector_begin,
    .end = vector_end,
    .next = vector_next,
    .current = vector_current};

Vector *vector_create(int length)
{
    vector_def *ret = NULL;

    if (length > 0)
    {
        ret = malloc(sizeof(vector_def));
        ret->head = malloc(sizeof(VectorNode) * length);
        if (ret && ret->head)
        {
            ret->current = NULL;
            ret->base.vtable = &s_vector_vtable;
            ret->base.length = length;
            for (int i = 0; i < length; i++)
            {
                ret->head[i] = NULL;
            }
        }
    }
    return (Vector *)ret;
}

bool vector_insert(Vector *list, int i, const VectorNode node)
{
    bool ret = true;
    vector_def *obj = (vector_def *)list;

    if (obj && (i >= 0) && (i < obj->base.length) && node)
    {
        for (int j = obj->base.length - 1; j > i; j--)
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

VectorNode vector_remove(Vector *list, int i)
{
    VectorNode ret = NULL;
    vector_def *obj = (vector_def *)list;

    if (obj && (i >= 0) && (i < obj->base.length))
    {
        for (int j = i + 1; j < obj->base.length; j++)
        {
            obj->head[j - 1] = obj->head[j];
        }
        ret = obj->head[i];
    }
    return ret;
}

int vector_find(Vector *list, const VectorNode node)
{
    int ret = -1;
    vector_def *obj = (vector_def *)list;

    if (obj && node)
    {
        for (int i = 0; i < obj->base.length; i++)
        {
            if (obj->head[i] == node)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

bool vector_get(Vector *list, int i, VectorNode *node)
{
    bool ret = true;
    vector_def *obj = (vector_def *)list;

    if (obj && (i >= 0) && (i < obj->base.length) && node)
    {
        *node = obj->head[i];
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool vector_set(Vector *list, int i, const VectorNode node)
{
    bool ret = true;
    vector_def *obj = (vector_def *)list;

    if (obj && (i >= 0) && (i < obj->base.length) && node)
    {
        obj->head[i] = node;
    }
    else
    {
        ret = false;
    }
    return ret;
}

int vector_length(Vector *list)
{
    int ret = 0;

    ret = (list) ? ((vector_def *)list)->base.length : (0);

    return ret;
}

void vector_destroy(Vector *list)
{
    if (list)
    {
        free(((vector_def *)list)->head);
        free(list);
    }
}

void vector_begin(Vector *list)
{
    if(list)
    {
        ((vector_def *)list)->current = ((vector_def *)list)->head;
    }
}

void vector_next(Vector *list)
{
    if(list)
    {
        ((vector_def *)list)->current = ((vector_def *)list)->current + 1;
    }
}

bool vector_end(Vector *list)
{
    bool ret = false;
    if(list)
    {
        vector_def *obj = list;
        ret = (obj->current == (obj->head + obj->base.length));
    }
    return ret;
}

VectorNode vector_current(Vector *list)
{
    return (list) ? (*((vector_def *)list)->current) : (NULL);
}