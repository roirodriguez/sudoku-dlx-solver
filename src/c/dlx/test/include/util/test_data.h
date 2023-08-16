#ifndef _KNUT_PAPER_DATA_H
#define _KNUT_PAPER_DATA_H


/* Returns first matrix example from knut's paper as a dlx grid */
struct Grid *get_knut_paper_basic_grid(void);


/* Returns first matrix example from knut's paper as a 2d boolean matrix */
struct BooleanMatrix *get_knut_paper_basic_matrix(void);
struct BooleanMatrix *get_knut_paper_matrix_col3_covered();
struct BooleanMatrix *get_knut_paper_matrix_col35_covered();


/* Utility function to compare two matrices, returns true if equal, false if different */
bool check_expected(struct BooleanMatrix *matrix, struct BooleanMatrix *expected);


/* Check cover solution represented as a BooleanMatrix is exact */
bool check_exact_cover(struct BooleanMatrix *sol_matrix);


/* Print a boolean matrix, for tracing purposes */
void print_boolean_matrix(struct BooleanMatrix *matrix);


#endif /* _KNUT_PAPER_DATA_H */