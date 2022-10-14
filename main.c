#include "err.h"
#include "vector.h"
#include "link_list.h"
#include "circle_list.h"
#include "dual_link_list.h"
#include "dual_circle_list.h"
#include <unistd.h>
#include <string.h>

#define MAX_LEN 10
static int array[MAX_LEN] = {0};

void function_test(list_obj_t *list)
{
    int i = 0;

    printf("type: %s\r\n", OBJECT_NAME(list));

    /* insert */
    for (i = 0; i < MAX_LEN; i++)
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

    /* set */
    for (i = 0; i < list_length(list); i++)
    {
        int val = MAX_LEN - i;
        list_set(list, i, &val);
    }

    /* get */
    printf("get: ");
    for (i = 0; i < list_length(list); i++)
    {
        int val = 0;
        list_get(list, i, &val);
        printf("%d ", val);
    }
    printf("\n");

    if (strcmp(OBJECT_NAME(list), "dual circle list") == 0)
    {
        /* pop front */
        printf("pop front: ");
        while (list_length(list))
        {
            int temp = 0;
            dual_circle_list_pop_front(list, &temp);
            printf("%d ", temp);
        }
        printf("\r\n");

        /* push front */
        printf("push front: ");
        for (i = 0; i < MAX_LEN; i++)
        {
            dual_circle_list_push_front(list, &i);
            printf("%d ", i);
        }
        printf("\r\n");

        /* pop back */
        printf("pop back: ");
        for (i = 0; i < MAX_LEN; i++)
        {
            int temp = 0;
            dual_circle_list_pop_back(list, &temp);
            printf("%d ", i);
        }
        printf("\r\n");

        /* push back */
        printf("push back: ");
        for (i = 0; i < MAX_LEN; i++)
        {
            dual_circle_list_push_back(list, &i);
            printf("%d ", i);
        }
        printf("\r\n");
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