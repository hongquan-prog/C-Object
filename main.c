#include "err.h"
#include "vector.h"
#include "link_list.h"
#include "circle_list.h"
#include "dual_link_list.h"
#include "dual_circle_list.h"
#include <unistd.h>

#define MAX_LEN 10
static int array[MAX_LEN] = {0};

void function_test(list_obj_t *list)
{
    int i = 0;

    printf("type: %s\r\n", list->class_p->type_name);

    /* insert */
    for (int i = 0; i < MAX_LEN; i++)
    {
        array[i] = i;
        list_insert(list, i, &array[i]);
    }

    /* traverse */
    printf("traverse: ");
    for (list_begin(list), i = 0; !list_end(list) && (i < list_length(list)); list_next(list), i++)
    {
        int *ret = list_current(list);
        printf("%d ", *ret);
    }
    printf("\n");

    /* find */
    for (i = 0; i < list_length(list); i++)
    {
        printf("%d position is: %d\r\n", array[i], list_find(list, &array[i]));
    }

    /* remove */
    while (list_length(list))
    {
        int ret = 0;
        list_get(list, 0, &ret);
        printf("remove %d\r\n", ret);
        list_remove(list, 0);
    }
}


int main()
{
    list_obj_t *list = NULL;
    list = vector_create(sizeof(int), MAX_LEN);
    function_test(list);
    list_delete(list);

    list = link_list_create(sizeof(int));
    function_test(list);
    list_delete(list);

    list = circle_list_create(sizeof(int));
    function_test(list);
    list_delete(list);

    list = dual_link_list_create(sizeof(int));
    function_test(list);
    list_delete(list);

    list = dual_circle_list_create(sizeof(int));
    function_test(list);
    list_delete(list);
}