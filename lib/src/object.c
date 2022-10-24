#include "object.h"
#include <stdlib.h>
#include <string.h>

static void obj_construct(obj_t *obj, obj_constructor_args_t *args);
static void obj_destruct(obj_t *obj);

obj_t *obj_class_create_obj(const obj_class_t *class, obj_constructor_args_t *args)
{
    uint32_t s = class->instance_size;
    obj_t *obj = malloc(s);

    if (NULL == obj)
    {
        return NULL;
    }

    obj->class = class;
    obj_construct(obj, args);

    return obj;
}

void obj_class_delete_obj(obj_t *obj)
{
    obj_destruct(obj);
    free(obj);
}
/*-----------------
 * static function
 *----------------*/

static void obj_construct(obj_t *obj, obj_constructor_args_t *args)
{
    const obj_class_t *original_class = obj->class;

    if (obj->class->base_class)
    {
        /*Don't let the descendant methods run during constructing the ancestor type*/
        obj->class = obj->class->base_class;

        /*Construct the base first*/
        obj_construct(obj, args);
    }

    /*Restore the original class*/
    obj->class = original_class;

    if (obj->class->constructor_cb)
    {
        obj->class->constructor_cb(obj, args);
    }
}

static void obj_destruct(obj_t *obj)
{
    if (obj->class->destructor_cb)
    {
        obj->class->destructor_cb(obj);
    }

    if (obj->class->base_class)
    {
        /*Don't let the descendant methods run during destructing the ancestor type*/
        obj->class = obj->class->base_class;

        /*Call the base class's destructor too*/
        obj_destruct(obj);
    }
}