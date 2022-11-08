#include "tree.h"

static void tree_constructor(obj_t *obj, obj_constructor_args_t *args);

const obj_class_t g_tree_class = {
    .vtable = NULL,
    .base_class = NULL,
    .constructor_cb = tree_constructor,
    .destructor_cb = NULL,
    .instance_size = sizeof(tree_obj_t),
    .class_name = "tree"};

static void tree_constructor(obj_t *obj, obj_constructor_args_t *args)
{
    tree_constructor_args_t *tree_args = (tree_constructor_args_t *)args;

    if (obj)
    {
        tree_obj_t *ret = (tree_obj_t *)obj;
        ret->item_size = *(tree_args->item_size);
        ret->equal = NULL;
        ret->root = NULL;
    }
}

void tree_delete(tree_obj_t *obj)
{
    obj_class_delete_obj((obj_t *)obj);
}

void tree_reload_equal(tree_obj_t *obj, equal_operator_t equal)
{
    if (obj)
    {
        obj->equal = equal;
    }
}

bool tree_insert(tree_obj_t *obj, const tree_value_t *value, tree_node_t *parent)
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->insert)
    {
        return vtable->insert(obj, value, parent);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "insert_value function not exist in vtable");
        return false;
    }
}

bool tree_remove(tree_obj_t *obj, tree_value_t *value)
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->remove)
    {
        return vtable->remove(obj, value);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "remove function not exist in vtable");
        return false;
    }
}

tree_node_t *tree_find(tree_obj_t *obj, tree_value_t *value) 
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->find)
    {
        return vtable->find(obj, value);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "find function not exist in vtable");
        return NULL;
    }
}

int tree_degree(tree_obj_t *obj) 
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->degree)
    {
        return vtable->degree(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "degree function not exist in vtable");
        return 0;
    }
}

int tree_count(tree_obj_t *obj) 
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->count)
    {
        return vtable->count(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "count function not exist in vtable");
        return 0;
    }
}

int tree_height(tree_obj_t *obj) 
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->height)
    {
        return vtable->height(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "height function not exist in vtable");
        return 0;
    }
}

void tree_clear(tree_obj_t *obj) 
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->clear)
    {
        vtable->clear(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "clear function not exist in vtable");
    }
}

void tree_begin(tree_obj_t *obj) 
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->begin)
    {
        vtable->begin(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "begin function not exist in vtable");
    }
}

bool tree_end(tree_obj_t *obj) 
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->end)
    {
        return vtable->end(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "end function not exist in vtable");
        return false;
    }
}

void tree_next(tree_obj_t *obj)
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->next)
    {
        vtable->next(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "next function not exist in vtable");
    }
}

tree_value_t *tree_current(tree_obj_t *obj)
{
    tree_vtable_t *vtable = (tree_vtable_t *)obj->class->vtable;
    
    if (vtable->current)
    {
        return vtable->current(obj);
    }
    else
    {
        LOG(ERR_CONSTRUCT(NullPointer), "current function not exist in vtable");
        return NULL;
    }
}