#include "err.h"
#include "vector.h"
#include "link_list.h"
#include "circle_list.h"
#include "dual_link_list.h"
#include "dual_circle_list.h"
#include "static_queue.h"
#include "link_queue.h"
#include "static_stack.h"
#include "link_stack.h"
#include "general_tree.h"
#include <unistd.h>
#include <string.h>

#define MAX_LEN 10
static int array[MAX_LEN] = {0};

void list_test(list_obj_t *list)
{
    int i = 0;

    printf("\r\ntype: %s\r\n", OBJECT_NAME(list));

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

    if (0 == strcmp(OBJECT_NAME(list), "dual circle list"))
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

void queue_test(queue_obj_t *obj)
{
    int i = 0;

    printf("\r\ntype: %s\r\n", OBJECT_NAME(obj));

    /* add */
    printf("add: ");
    for (i = 0; i < MAX_LEN; i++)
    {
        queue_add(obj, &i);
        printf("%d ", i);
    }
    printf("\r\n");

    /* remove */
    printf("remove: ");
    while (queue_length(obj))
    {
        int temp = 0;
        queue_front(obj, &temp);
        printf("%d ", temp);
        queue_remove(obj);
    }
    printf("\r\n");

    printf("add and remove: ");
    for (i = 0; i < 20; i++)
    {
        int temp = 0;
        queue_add(obj, &i);
        queue_front(obj, &temp);
        queue_remove(obj);
        printf("%d ", temp);
    }
    printf("\r\n");
}

void stack_test(stack_obj_t *obj)
{
    int i = 0;

    printf("\r\ntype: %s\r\n", OBJECT_NAME(obj));

    /* push */
    printf("push: ");
    for (i = 0; i < MAX_LEN; i++)
    {
        stack_push(obj, &i);
        printf("%d ", i);
    }
    printf("\r\n");

    /* pop */
    printf("pop: ");
    while (stack_size(obj))
    {
        int temp = 0;
        stack_top(obj, &temp);
        printf("%d ", temp);
        stack_pop(obj);
    }
    printf("\r\n");

    printf("push and pop: ");
    for (i = 0; i < 20; i++)
    {
        int temp = 0;
        stack_push(obj, &i);
        stack_top(obj, &temp);
        stack_pop(obj);
        printf("%d ", temp);
    }
    printf("\r\n");
}

void tree_test(tree_obj_t *obj)
{
    int val = 0;
    int find = 0;
    /* insert
     *         0
     *   1           2
     * 3   4      5  6  7
     */
    printf("\r\ntype: %s\r\n", OBJECT_NAME(obj));

    printf("insert:\r\n         0\r\n   1           2\r\n 3   4      5  6  7\r\n");
    tree_insert(obj, &val, NULL);
    find = 0;
    val = 1;
    tree_insert(obj, &val, tree_find(obj, &find));
    val = 2;
    tree_insert(obj, &val, tree_find(obj, &find));

    find = 1;
    val = 3;
    tree_insert(obj, &val, tree_find(obj, &find));
    val = 4;
    tree_insert(obj, &val, tree_find(obj, &find));

    find = 2;
    val = 5;
    tree_insert(obj, &val, tree_find(obj, &find));
    val = 6;
    tree_insert(obj, &val, tree_find(obj, &find));
    val = 7;
    tree_insert(obj, &val, tree_find(obj, &find));

    /* height */
    printf("height: %d \r\n", tree_height(obj));

    /* count */
    printf("count: %d \r\n", tree_count(obj));

    /* degree */
    printf("degree: %d \r\n", tree_degree(obj));

    /* traverse */
    printf("traverse: ");
    for (tree_begin(obj); !tree_end(obj); tree_next(obj))
    {
        printf("%d ", *((int *)tree_current(obj)));
    }
    printf("\r\n");

    /* remove */
    val = 2;
    tree_remove(obj, &val);
    printf("after 2 removed: \r\n     0\r\n   1\r\n 3   4\r\n");
    printf("traverse: ");
    for (tree_begin(obj); !tree_end(obj); tree_next(obj))
    {
        printf("%d ", *((int *)tree_current(obj)));
    }
    printf("\r\n");

    /* height */
    printf("height: %d \r\n", tree_height(obj));

    /* count */
    printf("count: %d \r\n", tree_count(obj));

    /* degree */
    printf("degree: %d \r\n", tree_degree(obj));
}

int main()
{
    list_obj_t *list = NULL;
    queue_obj_t *queue = NULL;
    stack_obj_t *stack = NULL;

    list = vector_create(sizeof(int), MAX_LEN);
    list_test(list);
    list_delete(list);

    list = link_list_create(sizeof(int));
    list_test(list);
    list_delete(list);

    list = circle_list_create(sizeof(int));
    list_test(list);
    list_delete(list);

    list = dual_link_list_create(sizeof(int));
    list_test(list);
    list_delete(list);

    list = dual_circle_list_create(sizeof(int));
    list_test(list);
    list_delete(list);

    queue = static_queue_create(sizeof(int), MAX_LEN);
    queue_test(queue);
    queue_delete(queue);

    queue = link_queue_create(sizeof(int));
    queue_test(queue);
    queue_delete(queue);

    stack = static_stack_create(sizeof(int), MAX_LEN);
    stack_test(stack);
    stack_delete(stack);

    stack = link_stack_create(sizeof(int));
    stack_test(stack);
    stack_delete(stack);

    tree_obj_t *tree = general_tree_create(sizeof(int));
    tree_test(tree);
    tree_delete(tree);
}