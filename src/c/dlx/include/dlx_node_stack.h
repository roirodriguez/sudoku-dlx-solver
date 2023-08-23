#ifndef _DLX_NODE_STACK_H
#define _DLX_NODE_STACK_H


#include "dlx_types.h"
#include "dlx.h"


struct NodeStack {
    dlx_size_t size;
    struct NodeStackItem *top;
};


struct NodeStackItem {
    struct Node *data_ptr;
    struct NodeStackItem *prev;
};


/* 
 * NodeStack is used for solution construction during search. 
 * The following are our stack related functions.
 */
struct NodeStack *new_node_stack(void);
void node_stack_push(struct Node *node, struct NodeStack *stack);
struct Node *node_stack_pop(struct NodeStack *stack);
void free_node_stack(struct NodeStack *stack);


#endif /* _DLX_NODE_STACK_H */