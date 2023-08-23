#ifndef _TEST_UTIL_H
#define _TEST_UTIL_H

#include "dlx.h"


/* Utility function to compare two matrices, returns true if equal, false if different */
bool check_expected(struct BooleanMatrix *matrix, struct BooleanMatrix *expected);


/* 
 * Checks if the given nodelist contains a set of row representatives (nodes) which are 
 * an exact cover of grid.
 */
bool check_exact_cover(struct Grid *grid, struct NodeList *lst);


/* Print a boolean matrix, for tracing purposes */
void print_boolean_matrix(struct BooleanMatrix *matrix);


#endif /* _TEST_UTIL_H */