#include <criterion/criterion.h>
#include "dlx.h"


struct Grid *grid;


void setup()
{
    grid = new_grid((dlx_size_t) 5);
}


void teardown()
{
    free_grid(grid);
}


Test(test_grid_creation, new_grid_test, .init=setup, .fini=teardown)
{
    cr_assert_eq(5, grid->n_cols, "Number of cols is 5.");
    cr_assert_eq(0, grid->n_rows, "Number of rows initialized to zero.");
    cr_assert_not_null(grid->solution_stack, "Solution stack is non-null initialized.");
    cr_assert_eq(0, grid->solution_stack->size, "Solution stack has initial size zero.");
}


Test(test_grid_creation, new_grid_right_test, .init=setup, .fini=teardown)
{
    struct Node *ptr = grid->root->right;
    for (int i=0; i<5; i++)
    {
        cr_assert_not_null(ptr);
        cr_assert_eq(&(grid->cols[i]), ptr, "Right pointer and corresponding col ptr are the same.");
        cr_assert_eq(i+1, ptr->dlx_column_idx, "Column idx is the expected and 1-based.");
        ptr = ptr->right;
    }
    cr_assert_eq(grid->root, ptr, "Right pointer comes back to the root.");
}


Test(test_grid_creation, new_grid_left_test, .init=setup, .fini=teardown)
{
    struct Node *ptr = grid->root->left;
    for (int i=5; i>0; i--)
    {
        cr_assert_not_null(ptr);
        cr_assert_eq(&(grid->cols[i-1]), ptr, "Left pointer and corresponding col ptr are the same.");
        cr_assert_eq(i, ptr->dlx_column_idx, "Column idx is the expected and 1-based.");        
        ptr = ptr->left;
    }
    cr_assert_eq(grid->root, ptr, "Left pointer comes back to the root.");
}