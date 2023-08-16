#include <stdlib.h>
#include "dlx.h"
#include "dlx_node_stack.h"


struct NodeStack *new_node_stack(void)
{
    return calloc(1, sizeof(struct NodeStack));
}


void free_node_stack(struct NodeStack *stack)
{
    if (stack != NULL)
    {
        struct NodeStackItem *prev, *ptr = stack->top;
        while (NULL != (prev = ptr->prev))
        {
            free(ptr);
            ptr = prev;
        }
        free(ptr);
        free(stack);
    }
}


void node_stack_push(struct Node *node, struct NodeStack *stack)
{
    if (node != NULL && stack != NULL)
    {
        struct NodeStackItem *new_item = malloc(sizeof(struct NodeStackItem));
        new_item->data_ptr = node;
        new_item->prev = stack->top;
        stack->top = new_item;
        stack->size++;
    }
    return;
}


struct Node *node_stack_pop(struct NodeStack *stack)
{
    if (stack != NULL && stack->size > 0)
    {
        struct Node *ret = stack->top->data_ptr;
        struct NodeStackItem *top = stack->top;
        stack->top = top->prev;
        stack->size--;
        free(top);
        return ret;
    }
    return NULL;
}
