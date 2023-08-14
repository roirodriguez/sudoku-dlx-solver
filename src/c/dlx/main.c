#include <stdio.h>

#include "dlx.h"
#include "sudoku.h"


int main(int argc, char **argv) 
{
    printf("%s\n", argv[1]);
    struct Grid *sudoku_grid = create_sudoku_grid(argv[1]);
    // solve
    while(search(sudoku_grid, sudoku_solution_printing_callback))
    {
        continue;
    }
    free_dlx_grid(sudoku_grid);
}