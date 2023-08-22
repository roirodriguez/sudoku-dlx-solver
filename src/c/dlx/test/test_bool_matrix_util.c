#include <stdbool.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "dlx_types.h"
#include "dlx_util.h"
#include "util/test_data_dlx.h"


#define strbool(a)  ((a)?"true":"false")


struct Grid *get_knut_paper_basic_grid(void);
struct BooleanMatrix *get_knut_paper_basic_matrix(void);


Test(test_bool_matrix_util, new_matrix_test)
{
    struct BooleanMatrix *matrix = new_boolean_matrix(5, 6);
    cr_assert_eq(5, matrix->n_rows, "n_rows initialized to 5");
    cr_assert_eq(6, matrix->n_cols, "n_cols initialized to 6");
    dlx_size_t i, j;
    for (i=0; i < matrix->n_rows; i++)
        for(j=0; j < matrix->n_cols; j++)
            cr_assert_eq(false, matrix->matrix[i][j], "Element (%d, %d) set to false.", i, j);
    free_boolean_matrix(matrix);
}


Test(test_bool_matrix_util, get_grid_boolean_matrix_repr_test)
{
    struct Grid *grid = get_knut_paper_basic_grid();
    struct BooleanMatrix *knut_matrix, *knut_grid_matrix;
    knut_matrix = get_knut_paper_basic_matrix();
    knut_grid_matrix = get_grid_boolean_matrix_repr(grid);
    dlx_size_t i, j;
    for (i=0; i<knut_matrix->n_rows; i++)
        for(j=0; j<knut_matrix->n_cols; j++)
            if (knut_matrix->matrix[i][j] != knut_grid_matrix->matrix[i][j])
                cr_fail("Matrix at (%d, %d) was %s, grid was %s.", i, j,
                    strbool(knut_matrix->matrix[i][j]), strbool(knut_grid_matrix->matrix[i][j]));
    free_boolean_matrix(knut_matrix);
    free_boolean_matrix(knut_grid_matrix);
    free_grid(grid);
}


Test(test_bool_matrix_util, new_grid_from_bool_matrix_test)
{
    struct Grid *grid;
    struct BooleanMatrix *knut_matrix, *knut_grid_matrix;
    knut_matrix = get_knut_paper_basic_matrix();
    grid = new_grid_from_bool_matrix(knut_matrix);
    knut_grid_matrix = get_grid_boolean_matrix_repr(grid);
    dlx_size_t i, j;
    for (i=0; i<knut_matrix->n_rows; i++)
        for(j=0; j<knut_matrix->n_cols; j++)
            if (knut_matrix->matrix[i][j] != knut_grid_matrix->matrix[i][j])
                cr_fail("Matrix at (%d, %d) was %s, grid was %s.", i, j,
                    strbool(knut_matrix->matrix[i][j]), strbool(knut_grid_matrix->matrix[i][j]));
    free_boolean_matrix(knut_matrix);
    free_boolean_matrix(knut_grid_matrix);
    free_grid(grid);
}
