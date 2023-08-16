#ifndef _DLX_UTIL_H
#define _DLX_UTIL_H

#include <stdbool.h>
#include "dlx.h"
#include "dlx_types.h"


struct BooleanMatrix
{
    bool **matrix;
    dlx_size_t n_rows;
    dlx_size_t n_cols;
};


/* Allocates space for a boolean matrix, initialized to all false values. */
struct BooleanMatrix *new_boolean_matrix(dlx_size_t n_rows, dlx_size_t n_cols);
void free_boolean_matrix(struct BooleanMatrix *matrix);


/* Constructs a grid from a 2d array of bools */
struct Grid *new_grid_from_bool_matrix(struct BooleanMatrix *matrix);


/* 
 * Returns a 2d array of bools representing the given Grid. This is compatible
 * with a covered grid, returning zeros in that case where corresponds. Mainly
 * for testing purposes.
 */
struct BooleanMatrix *get_grid_boolean_matrix_repr(struct Grid *grid);


/* 
 * Returns a BooleanMatrix representation of a dlx problem solution. Rows are not
 * guarranteed to be ordered by grid order.
 */
struct BooleanMatrix *get_solution_boolean_matrix_repr(struct Grid *solved_grid);


#endif /* _DLX_UTIL_H */
