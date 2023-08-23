#ifndef _SUDOKU_H
#define _SUDOKU_H

#include "dlx.h"
#include "dlx_util.h"


#define _MAX_DIMENSION  3


struct SudokuGrid {
    struct Grid *grid;
    dlx_size_t dim;
    dlx_size_t max_digit;
    dlx_size_t size;
    dlx_size_t n_restrictions;
    struct NodeList *_malloced_node_ptrs;
};


struct SudokuGrid *new_sudoku_grid (char *puzzle_str);
void free_sudoku_grid(struct SudokuGrid *grid);


#endif /* _SUDOKU_H */