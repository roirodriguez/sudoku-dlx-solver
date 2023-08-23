#ifndef _TEST_DATA_DLX_H
#define _TEST_DATA_DLX_H

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


#endif /* _TEST_DATA_DLX_H */