#ifndef _SUDOKU_H
#define _SUDOKU_H

#include "dlx.h"

#define DIM             ((dlx_size_t) 3)
#define MAX_DIGIT       ((dlx_size_t) DIM*DIM)
#define SIZE            ((dlx_size_t) MAX_DIGIT*MAX_DIGIT)
#define N_RESTRICTIONS  ((dlx_size_t) 4 * SIZE)


struct Grid *create_sudoku_grid (char *puzzle_str);
void sudoku_solution_printing_callback(void);


#endif /* _SUDOKU_H */