#include <stdio.h>
#include <stdlib.h>

#include "dlx.h"
#include "dlx_util.h"
#include "sudoku.h"


struct SolutionList *solution_lst = NULL;
struct SudokuGrid *sudoku_grid = NULL;

void search_solution_printing_callback(struct Grid *solved_grid);


int main(int argc, char **argv)
{
    sudoku_grid = new_sudoku_grid(argv[1]);
    search(sudoku_grid->grid, search_solution_printing_callback);
    free_sudoku_grid(sudoku_grid);
    return 0;
}


void search_solution_printing_callback(struct Grid *solved_grid)
{
    struct NodeStackItem *stack_ptr = solved_grid->solution_stack->top;
    dlx_size_t cellidx, value;
    char *solution = malloc(sudoku_grid->size * sizeof(char) + 1);
    solution[sudoku_grid->size] = '\0';

    while(stack_ptr != NULL)
    {
        /* dlx row num gives us cell and value */
        cellidx = stack_ptr->data_ptr->dlx_row_idx / sudoku_grid->max_digit;
        value = 1 + stack_ptr->data_ptr->dlx_row_idx % sudoku_grid->max_digit;
        solution[cellidx] = 48 + value;
        stack_ptr = stack_ptr->prev;
    }

    puts(solution);
}