#include "err.h"
#include "Vector.h"
#include "LinkList.h"
#include "CircleList.h"
#include "DualLinkList.h"
#include "DualCircleList.h"
#include <unistd.h>

#define MAX_LEN 10

struct list_node
{
    struct dual_link_list_node next;
    int data;
};
// 10个链表节点
struct list_node array1[MAX_LEN] = {0};
// 10顺序表节点
int array2[MAX_LEN];

int main()
{
    // 顺序表
    Vector *list = vector_create(MAX_LEN);
    for (int i = 0; i < MAX_LEN; i++)
    {
        array2[i] = i;
        list_insert(list, i, &array2[i]);
    }
    printf("list length:%d\n", list_length(list));
    for(list_begin(list); !list_end(list); list_next(list))
    {
        int* ret = list_current(list);
        printf("%d ", *ret);
    }
    printf("\n");
    list_destory(list);

    // 单链表
    list = link_list_create();
    for (int i = 0; i < MAX_LEN; i++)
    {
        array1[i].data = MAX_LEN - i;
        list_insert(list, i, &array1[i]);
    }
    printf("list length:%d\n", list_length(list));
    for(list_begin(list); !list_end(list); list_next(list))
    {
        struct list_node* ret = list_current(list);
        printf("%d ", ret->data);
    }
    printf("\n");
    list_destory(list);

    // 循环链表
    list = circle_list_create();
    for (int i = 0; i < MAX_LEN; i++)
    {
        array1[i].data = i;
        list_insert(list, i, &array1[i]);
    }
    printf("list length:%d\n", list_length(list));
    // for(list_begin(list); !list_end(list); list_next(list))
    // {
    //     struct list_node* ret = list_current(list);
    //     printf("%d \n", ret->data);
    //     sleep(1);
    // }
    printf("\n");
    list_destory(list);

    // 双链表
    list = dual_link_list_create();
    for (int i = 0; i < MAX_LEN; i++)
    {
        array1[i].data = MAX_LEN - i;
        list_insert(list, i, &array1[i]);
    }
    printf("list length:%d\n", list_length(list));
    for(list_begin(list); !list_end(list); list_next(list))
    {
        struct list_node* ret = list_current(list);
        printf("%d ", ret->data);
    }
    printf("\n");
    list_destory(list);

    // 循环双链表
    list = dual_circle_list_create();
    for (int i = 0; i < MAX_LEN; i++)
    {
        array1[i].data = i;
        list_insert(list, i, &array1[i]);
    }
    printf("list length:%d\n", list_length(list));
    // for(list_begin(list); !list_end(list); list_next(list))
    // {
    //     struct list_node* ret = list_current(list);
    //     printf("%d \n", ret->data);
    //     sleep(1);
    // }
    printf("\n");
    list_destory(list);
}