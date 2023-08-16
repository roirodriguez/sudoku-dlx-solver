#ifndef _KNUT_PAPER_DATA_H
#define _KNUT_PAPER_DATA_H


/* Returns first matrix example from knut's paper as a dlx grid */
struct Grid *get_knut_paper_basic_grid(void);


/* Returns first matrix example from knut's paper as a 2d boolean matrix */
struct BooleanMatrix *get_knut_paper_basic_matrix(void);


#endif /* _KNUT_PAPER_DATA_H */