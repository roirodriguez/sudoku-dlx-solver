#include <stdio.h>
#include <stdlib.h>

#include "dlx.h"
#include "sudoku.h"

int main(void) 
{
    char *puzzle_str = "0000000000000000";
    struct SudokuGrid *sudoku_grid = new_sudoku_grid(puzzle_str);
    printf("test");
    free_sudoku_grid(sudoku_grid);
    return 0;
}
