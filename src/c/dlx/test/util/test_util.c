#include <stdio.h>
#include <stdbool.h>

#include "dlx_util.h"

bool check_expected(struct BooleanMatrix *matrix, struct BooleanMatrix *expected)
{
    bool check = true;
    for (int i=0; i<matrix->n_rows; i++)
        for (int j=0; j<matrix->n_cols; j++)
            check &= (matrix->matrix[i][j] == expected->matrix[i][j]);
    return check;
}


struct BooleanMatrix *_nodelist_to_matrix(struct Grid *grid, struct NodeList *lst)
{
    if (grid == NULL || lst == NULL)
        return NULL;
    
    struct BooleanMatrix *mat = new_boolean_matrix(lst->size, grid->n_cols);
    for (int i=0; i<lst->size; i++)
    {
        struct Node *row_ptr = lst->list[i];
        do
        {
            mat->matrix[i][row_ptr->dlx_column_idx] = true;
        } while (lst->list[i] != (row_ptr = row_ptr->right));        
    }
    
    return mat;
}


bool check_exact_cover(struct Grid *grid, struct NodeList *lst)
{
    struct BooleanMatrix *sol_matrix = _nodelist_to_matrix(grid, lst);
    bool check = false;
    for (dlx_size_t j=0; j<sol_matrix->n_cols; j++)
    {
        for (dlx_size_t i=0; i<sol_matrix->n_rows; i++)
            check ^= sol_matrix->matrix[i][j];
        if (!check) return false;
        check = false;
    }
    return true;
}


void print_boolean_matrix(struct BooleanMatrix *matrix)
{
    for (int i=0; i<matrix->n_rows; i++)
    {
        for (int j=0; j<matrix->n_cols; j++)
            printf("%d ", matrix->matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}
