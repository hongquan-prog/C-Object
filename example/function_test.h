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
#include "binary_tree.h"
#include "general_tree.h"
#include <unistd.h>
#include <string.h>

#define ARRAY_MAX_LEN 10

void list_test(list_obj_t *list);
void queue_test(queue_obj_t *obj);
void stack_test(stack_obj_t *obj);
void general_tree_test(tree_obj_t *obj);
void binary_tree_test(tree_obj_t *obj);