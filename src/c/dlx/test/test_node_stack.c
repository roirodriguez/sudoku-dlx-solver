#include <criterion/criterion.h>
#include "dlx_node_stack.h"
#include "dlx.h"


struct NodeStack *test_stack;
struct Node *node1, *node2;


void setup(void)
{
    test_stack = new_node_stack();
    node1 = calloc(1, sizeof(struct Node));
    node2 = calloc(1, sizeof(struct Node));
    node_stack_push(node1, test_stack);
    node_stack_push(node2, test_stack);
}


void teardown(void)
{
    free_node_stack(test_stack);
}


Test(test_node_stack, new_node_stack_test)
{
    struct NodeStack *stack = new_node_stack();
    cr_assert_eq(stack->top, NULL, "A stack is zero initialized.");
    cr_assert_eq(stack->size, 0, "Initial size of the stack is zero.");
}


Test(test_node_stack, test_setup, .init=setup, .fini=teardown)
{
    cr_assert_eq(test_stack->size, 2, "Test setup is correct, having an stack with 2 elements.");
}


Test(test_node_stack, node_stack_push_test, .init=setup, .fini=teardown)
{
    struct Node *node3 = calloc(1, sizeof(struct Node));
    node_stack_push(node3, test_stack);
    cr_assert_eq(3, test_stack->size, "After pushing stack size was incremented.");
    cr_assert_eq(node3, test_stack->top->data_ptr, "After pushing top points to the element inserted.");
}


Test(test_node_stack, node_stack_pop_test, .init=setup, .fini=teardown)
{
    struct Node *ptr = node_stack_pop(test_stack);
    cr_assert_eq(ptr, node2, "Pop returns pointer to popped element.");
    cr_assert_eq(1, test_stack->size, "Stack size is decremented after popping.");
    cr_assert_eq(node1, test_stack->top->data_ptr, "Top points to previous element after popping.");
}
