#ifndef _DLX_H
#define _DLX_H

#include <stdbool.h>
#include "dlx_types.h"
#include "dlx_node_stack.h"


struct Node {
    struct Node *up;
    struct Node *down;
    struct Node *right;
    struct Node *left;
    struct Node *column;
    dlx_size_t dlx_column_idx;
    dlx_size_t dlx_row_idx;
    dlx_size_t size;
};


struct Grid {
    struct Node *root;
    struct Node *cols;
    struct NodeStack *solution_stack;
    dlx_size_t n_rows;
    dlx_size_t n_cols;
};


/*
 * Helper functions for creating / freeing Nodes and Grids.
 */
struct Grid *new_grid(dlx_size_t n_cols);
void free_grid(struct Grid *);  // does not free nodes, only cols and root. implement one free function per builder.

/*
 * DLX related functions.
 */
void cover(struct Node *column);
void uncover(struct Node *column);
struct Node *choose_column(struct Node *root_node);
struct Node *choose_grid_column(struct Grid *grid);
bool search(struct Grid *grid, void (*sol_callback)(struct Grid *grid));


#endif /* _DLX_H */
