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


struct NodeList
{
    struct Node **list;
    dlx_size_t size;
};


struct SolutionList
{
    struct NodeList **list;
    dlx_size_t max_size;
    dlx_size_t used_size;
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


/* Solution list related functions */
struct NodeList *new_node_list(dlx_size_t size);
void free_node_list(struct NodeList *list);
struct SolutionList *new_solution_list(dlx_size_t max_size);
void free_solution_list(struct SolutionList *solution_lst);


/*
 * A default solution callback for search() util for most situations. It will copy
 * the node pointers inside the grid's solution_stack into a NodeList and insert 
 * that into the given SolutionList. As the callback only admits one parameter, this
 * is an utility function to be wrapped like the following:
 * 
 * // global
 * struct SolutionList *solution_lst;
 * 
 * void actual_callback(struct Grid *grid)
 * {
 *     default_solution_callback_template(grid, solution_lst);
 * }
 */
void default_solution_callback_template(struct Grid *solved_grid, struct SolutionList *solution_lst);

#endif /* _DLX_UTIL_H */
