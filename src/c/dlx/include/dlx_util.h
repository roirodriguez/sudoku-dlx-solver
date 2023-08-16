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


/* allocates space for a boolean matrix, boolean matrix initialized to all false. */
struct BooleanMatrix *new_boolean_matrix(dlx_size_t n_rows, dlx_size_t n_cols);
void free_boolean_matrix(struct BooleanMatrix *matrix);


/* constructs a grid from a 2d array of bools */
struct Grid *new_grid_from_bool_matrix(struct BooleanMatrix *matrix);


/* returns a 2d array of bools representing the given Grid */
struct BooleanMatrix *get_grid_boolean_matrix_repr(struct Grid *grid);

#endif /* _DLX_UTIL_H */
