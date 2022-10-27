#pragma once

#include "err.h"

typedef struct _obj_t obj_t;
typedef void obj_constructor_args_t;
typedef void obj_vtable_t;

typedef struct _obj_class_t
{
    const obj_vtable_t *vtable;
    const struct _obj_class_t *base_class;
    void (*constructor_cb)(obj_t *obj, obj_constructor_args_t *args);
    void (*destructor_cb)(obj_t *obj);
    int instance_size;
    const char *class_name;
} obj_class_t;

/******************************** obj_t *******************************************/

#define OBJ_MEMBER          const obj_class_t *class; 

struct _obj_t
{
    OBJ_MEMBER
};

#define OBJECT_NAME(__HANDLE__)  ((__HANDLE__)->class->class_name)

obj_t *obj_class_create_obj(const obj_class_t *class, obj_constructor_args_t *args);
void obj_class_delete_obj(obj_t *obj);