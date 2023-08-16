#include <stdlib.h>
#include <stdbool.h>

#include "dlx_util.h"
#include "dlx_types.h"
#include "dlx.h"


struct BooleanMatrix *new_boolean_matrix(dlx_size_t n_rows, dlx_size_t n_cols)
{
    struct BooleanMatrix *matrix = malloc(sizeof(struct BooleanMatrix));
    matrix->n_rows = n_rows;
    matrix->n_cols = n_cols;
    matrix->matrix = malloc(n_rows * sizeof(bool *));
    bool *ptr = calloc(n_rows * n_cols, sizeof(bool));
    for(int i=0; i<n_rows; i++)
        matrix->matrix[i] = (ptr + i* n_cols * sizeof(bool));
    return matrix;
}


void free_boolean_matrix(struct BooleanMatrix *matrix)
{
    free(matrix->matrix);
    free(matrix);
}


struct Grid *new_grid_from_bool_matrix(struct BooleanMatrix *matrix)
{
    if (matrix != NULL)
    {
        dlx_size_t i, j;
        struct Grid *grid = new_grid(matrix->n_cols);
        grid->n_rows = matrix->n_rows;
        struct Node **upper_nodes = malloc(matrix->n_cols * sizeof(struct Node *));
        for (j=0; j<matrix->n_cols; j++)
            upper_nodes[j] = &(grid->cols[j]);

        // We will insert row by row, keeping track in upper_nodes of
        // the last inserted node in each column.
        struct Node *ptr, *first = NULL, *left = NULL;
        for (i=0; i<matrix->n_rows; i++)
        {
            for (j=0; j<matrix->n_cols; j++)
            {
                if (matrix->matrix[i][j])
                {
                    ptr = calloc(1, sizeof(struct Node));
                    ptr->dlx_column_idx = j;
                    ptr->dlx_row_idx = i;
                    ptr->column = &(grid->cols[j]);
                    if (first == NULL)
                        first = ptr;
                    // link to the last in row
                    if (left != NULL)
                    {
                        ptr->left = left;
                        left->right = ptr;
                    }
                    left = ptr;
                    // link to the last in column
                    ptr->up = upper_nodes[j];
                    upper_nodes[j]->down = ptr;
                    upper_nodes[j] = ptr;
                }
            }
            // finish row linking
            first->left = left;
            left->right = first;
        }

        // finish column linking
        for(j=0; j<matrix->n_cols; j++)
        {
            upper_nodes[j]->down = &(grid->cols[j]);
            grid->cols[j].up = upper_nodes[j];
        }

        return grid;
    }
    return NULL;
}


struct BooleanMatrix *get_grid_boolean_matrix_repr(struct Grid *grid)
{
    if (grid != NULL)
    {
        dlx_size_t i, j;
        struct BooleanMatrix *matrix = new_boolean_matrix(grid->n_rows, grid->n_cols);
        struct Node *node_ptr, *col_ptr;
        col_ptr = grid->root;
        while(grid->root != (col_ptr = col_ptr->right))
        {
            node_ptr = col_ptr;
            while (col_ptr != (node_ptr = node_ptr->down))
            {
                i = node_ptr->dlx_row_idx;
                j = node_ptr->dlx_column_idx;
                matrix->matrix[i][j] = true;
            }
        }
        return matrix;
    }
    return NULL;
}


struct BooleanMatrix *get_solution_boolean_matrix_repr(struct Grid *solved_grid)
{
    if (solved_grid != NULL)
    {
        struct NodeStack *stack = solved_grid->solution_stack;
        struct BooleanMatrix *matrix = new_boolean_matrix(stack->size, solved_grid->n_cols);
        struct NodeStackItem *ptr = stack->top;
        struct Node *row_ptr;
        dlx_size_t i=0;
        while(ptr != NULL)
        {
            row_ptr = ptr->data_ptr;
            while(ptr->data_ptr != (row_ptr = row_ptr->right))
                matrix->matrix[i][row_ptr->dlx_column_idx] = true;
            ptr = ptr->prev;
            i++;
        }
        return matrix;
    }
    return NULL;
}
