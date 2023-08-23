#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "dlx.h"
#include "dlx_util.h"
#include "sudoku.h"
#include "util/test_util.h"


struct SudokuGrid *sudoku_grid = NULL;
struct SolutionList *solution_lst = NULL;


void solution_callback(struct Grid *solved_grid);


void setup()
{
    solution_lst = new_solution_list(50);
}

void teardown()
{
    free_solution_list(solution_lst);
    free_sudoku_grid(sudoku_grid);
}


Test(test_sudoku_grid, sudoku_solving_2x2_unique, .init=setup, .fini=teardown)
{
    char *puzzle_str = "1002000004300000";
    sudoku_grid = new_sudoku_grid(puzzle_str);
    search(sudoku_grid->grid, solution_callback);

    // check only one solution, and solution is an exact cover
    cr_assert_eq(1, solution_lst->used_size, "There is a unique solution.");
    cr_assert(check_exact_cover(sudoku_grid->grid, solution_lst->list[0]));
}


Test(test_sudoku_grid, sudoku_solving_2x2_multisol, .init=setup, .fini=teardown)
{
    char *puzzle_str = "1002000002100000";
    sudoku_grid = new_sudoku_grid(puzzle_str);
    search(sudoku_grid->grid, solution_callback);

    // check 4 solutions, and they are an exact cover
    cr_assert_eq(4, solution_lst->used_size, "There are exactly 4 solutions.");
    for(dlx_size_t i = 0; i < solution_lst->used_size; i++)
    {
        cr_assert(check_exact_cover(sudoku_grid->grid, solution_lst->list[i]));
    }
}


Test(test_sudoku_grid, sudoku_solving_2x2_nosol, .init=setup, .fini=teardown)
{
    char *puzzle_str = "1002000002100300";
    sudoku_grid = new_sudoku_grid(puzzle_str);
    search(sudoku_grid->grid, solution_callback);

    // check no solutions
    cr_assert_eq(0, solution_lst->used_size, "There are no solutions.");
}


Test(test_sudoku_grid, sudoku_solving_3x3_unique, .init=setup, .fini=teardown)
{
    char *puzzle_str = "006700100000004078105000000004000037030409050000060020800030010000051000000007209";
    sudoku_grid = new_sudoku_grid(puzzle_str);
    search(sudoku_grid->grid, solution_callback);

    // check only one solution, and solution is an exact cover
    cr_assert_eq(1, solution_lst->used_size, "There is a unique solution.");
    cr_assert(check_exact_cover(sudoku_grid->grid, solution_lst->list[0]));
}


Test(test_sudoku_grid, sudoku_solving_3x3_multisol, .init=setup, .fini=teardown)
{
    char *puzzle_str = "000008600003200040060030000802000904600700520050000000000694080300000061000000002";
    sudoku_grid = new_sudoku_grid(puzzle_str);
    search(sudoku_grid->grid, solution_callback);

    // check 4 solutions, and they are an exact cover
    cr_assert_eq(34, solution_lst->used_size, "There are exactly 34 solutions.");
    for(dlx_size_t i = 0; i < solution_lst->used_size; i++)
    {
        cr_assert(check_exact_cover(sudoku_grid->grid, solution_lst->list[i]));
    }
}


Test(test_sudoku_grid, sudoku_solving_3x3_nosol, .init=setup, .fini=teardown)
{
    char *puzzle_str = "000800610003007000400050080000020501090060000000004906109370000750001003600000020";
    sudoku_grid = new_sudoku_grid(puzzle_str);
    search(sudoku_grid->grid, solution_callback);

    // check no solutions
    cr_assert_eq(0, solution_lst->used_size, "There are no solutions.");
}


void solution_callback(struct Grid *solved_grid)
{
    default_solution_callback_template(solved_grid, solution_lst);
}