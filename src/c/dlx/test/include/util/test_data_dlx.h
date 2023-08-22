#ifndef _KNUT_PAPER_DATA_H
#define _KNUT_PAPER_DATA_H

#include "dlx.h"
#include "dlx_util.h"


/* Returns first matrix example from knut's paper as a dlx grid */
struct Grid *get_knut_paper_basic_grid(void);
struct Grid *get_knut_paper_nosol_grid(void);
struct Grid *get_knut_paper_3sol_grid(void);
void free_knut_paper_basic_grid(struct Grid *grid);
void free_knut_paper_3sol_grid(struct Grid *grid);


/* Returns first matrix example from knut's paper as a 2d boolean matrix */
struct BooleanMatrix *get_knut_paper_basic_matrix(void);
struct BooleanMatrix *get_knut_paper_matrix_col3_covered();
struct BooleanMatrix *get_knut_paper_matrix_col35_covered();


/* Utility function to compare two matrices, returns true if equal, false if different */
bool check_expected(struct BooleanMatrix *matrix, struct BooleanMatrix *expected);


/* 
 * Checks if the given nodelist contains a set of row representatives (nodes) which are 
 * an exact cover of grid.
 */
bool check_exact_cover(struct Grid *grid, struct NodeList *lst);


/* Print a boolean matrix, for tracing purposes */
void print_boolean_matrix(struct BooleanMatrix *matrix);


#endif /* _KNUT_PAPER_DATA_H */