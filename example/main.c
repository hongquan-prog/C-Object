#include "function_test.h"

int main()
{
    list_obj_t *list = NULL;
    queue_obj_t *queue = NULL;
    stack_obj_t *stack = NULL;
    tree_obj_t *tree = NULL;

    list = vector_create(sizeof(int), ARRAY_MAX_LEN);
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

    queue = static_queue_create(sizeof(int), ARRAY_MAX_LEN);
    queue_test(queue);
    queue_delete(queue);

    queue = link_queue_create(sizeof(int));
    queue_test(queue);
    queue_delete(queue);

    stack = static_stack_create(sizeof(int), ARRAY_MAX_LEN);
    stack_test(stack);
    stack_delete(stack);

    stack = link_stack_create(sizeof(int));
    stack_test(stack);
    stack_delete(stack);

    tree = general_tree_create(sizeof(int));
    general_tree_test(tree);
    tree_delete(tree);

    tree = binary_tree_create(sizeof(int));
    binary_tree_test(tree);
    tree_delete(tree);
}