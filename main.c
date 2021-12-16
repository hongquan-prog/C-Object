#include "err.h"
#include "Vector.h"
#include "LinkList.h"

#define MAX_LEN 10

struct list_node
{
    struct link_list_node next;
    int data;
};

// 100个链表节点
struct list_node  array1[MAX_LEN] = {0};
// 100个顺序表节点
int array2[MAX_LEN];

// 读取数据
VectorNode read_data(Vector* list, int i)
{
    VectorNode ret = NULL;
    // 使用各自的函数将数据进行获取
    (*((vector_vtable**)list))->get(list, i, &ret);
    return ret;
}

// 写入数据
void write_data(Vector* list, int i, VectorNode node)
{
    (*((vector_vtable**)list))->insert(list, i, node);
}

int main()
{
    LinkList* list = link_list_create();
    Vector* vector = vector_create(MAX_LEN);
    
    // 将数据插入表中
    for(int i = 0; i < MAX_LEN; i++)
    {
        array1[i].data = MAX_LEN - i;
        array2[i] = i;
        write_data(list, i, &array1[i]);
        write_data(vector, i, &array2[i]);
    }

    printf("list length:%d\n", vector_length(list));
    printf("vector length:%d\n", vector_length(vector));

    // 输出链表中的值
    printf("list:");
    for(int i = 0; i < MAX_LEN; i++)
    {
        struct list_node* ret = read_data(list, i);
        printf("%d ", ret->data);
    }
    printf("\n");

    // 输出顺序表中的值
    printf("vector:");
    for(int i = 0; i < MAX_LEN; i++)
    {
        int* ret = read_data(vector, i);
        printf("%d ", *ret);
    }
    printf("\n");

    vector_clear(vector);
    link_list_clear(list);
}