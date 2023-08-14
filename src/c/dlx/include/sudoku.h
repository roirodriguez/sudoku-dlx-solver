#ifndef _SUDOKU_H
#define _SUDOKU_H

#include "dlx.h"

struct Grid *create_sudoku_grid (char *puzzle_str);
void sudoku_solution_printing_callback(void);

#endif