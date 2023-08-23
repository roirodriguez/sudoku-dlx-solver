#include <stdio.h>
#include <stdlib.h>

#include "dlx.h"
#include "dlx_util.h"
#include "sudoku.h"


struct SolutionList *solution_lst = NULL;


int main(int argc, char **argv)
{
    struct SudokuGrid *sudoku_grid = new_sudoku_grid(argv[1]);
    search(sudoku_grid->grid, search_solution_printing_callback);
    free_sudoku_grid(sudoku_grid);
    return 0;
}
