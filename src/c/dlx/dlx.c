#include <stdlib.h>
#include <stdbool.h>

#include "dlx.h"

struct Node *create_empty_node(void) 
{
    struct Node *ret = malloc(sizeof(struct Node *));
    ret = calloc(1, sizeof(struct Node));
    return ret;
}


void cover(struct Node *column)
{
    struct Node *down, *up, *right, *left;
    struct Node *right_iter, *down_iter = column;

    // delete / skip column from header
    right = column->right;
    left = column->left;
    right->left = left;
    left->right = right;

    // delete / skip each 1 in this column
    while(column != (down_iter = down_iter->down)) 
    {
        right_iter = down_iter;
        while (down_iter != (right_iter = right_iter->right))
        {
            up = right_iter->up;
            down = right_iter->down;
            up->down = down;
            down->up = up;
            right_iter->column->size--;
        }
    }
}


void uncover(struct Node *column)
{
    struct Node *down, *up, *right, *left;
    struct Node *left_iter, *up_iter = column;

    // insert again 1s in this column
    while(column != (up_iter = up_iter->up)) 
    {
        left_iter = up_iter;
        while (up_iter != (left_iter = left_iter->left))
        {
            up = left_iter->up;
            down = left_iter->down;
            up->down = left_iter;
            down->up = left_iter;
            left_iter->column->size++;
        }
    }

    // insert again column to header
    right = column->right;
    left = column->left;
    right->left = column;
    left->right = column;    
}


struct Node *choose_column(struct Node *root_node)
{
    struct Node *column_ptr = root_node->right;
    unsigned short min_size = column_ptr->size;
    struct Node *min_col = column_ptr;

    while (root_node != (column_ptr = column_ptr->right))
    {
        if (column_ptr->size < min_size) 
        {
            min_col = column_ptr;
            min_size = min_col->size;
        }
    }

    return min_col;
};


struct Node *choose_grid_column(struct Grid *grid)
{
    return choose_column(grid->root);
}


void append_solution(struct Grid *grid, struct Node *row)
{
    struct DlxSolutionItem *solution = (struct DlxSolutionItem *) malloc(sizeof(struct DlxSolutionItem));
    solution->next = NULL;
    solution->solution = row;
    if (grid->solution_last == NULL)
    {
        solution->prev = NULL;
        grid->solution_first = grid->solution_last = solution;
        return;
    }
    grid->solution_last->next = solution;
    solution->prev = grid->solution_last;
    grid->solution_last = solution;
    return;
}


void pop_solution(struct Grid *grid)
{
    if (grid->solution_last != NULL)
    {
        struct DlxSolutionItem *popped = grid->solution_last;
        popped->prev->next = NULL;
        grid->solution_last = popped->prev;
        free(popped);
    }
}


bool search(struct Grid *grid, void (*sol_callback)(void))
{
    if (grid->root->right == grid->root)
    {
        // found a solution!
        (*sol_callback)();
        return true;
    }

    struct Node *column = choose_grid_column(grid);
    if (column->size == 0)
        return false;

    cover(column);
    
    struct Node *down_iter = column;
    struct Node *side_iter;
    while (column != (down_iter = down_iter->down))
    {
        append_solution(grid, down_iter);
        side_iter = down_iter;
        while (down_iter != (side_iter = side_iter->right))
        {
            cover(side_iter->column);
        }
        search(grid, sol_callback);
        pop_solution(grid);
        side_iter = down_iter;
        while (down_iter != (side_iter = side_iter->left))
        {
            uncover(side_iter->column);
        }
    }

    uncover(column);
    return false;
}


void free_dlx_grid(struct Grid *)
{

}
