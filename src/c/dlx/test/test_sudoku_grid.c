#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "sudoku.h"


struct SudokuGrid *sudoku_grid = NULL;


void setup()
{
}


void teardown()
{
    free_sudoku_grid(sudoku_grid);
}


Test(test_sudoku_grid, sudoku_properties_test_empty_2x2, .fini=teardown)
{
    char *puzzle_str = "0000000000000000";
    sudoku_grid = new_sudoku_grid(puzzle_str);

    cr_assert_eq(2, sudoku_grid->dim, "Dim expected to be 2.");
    cr_assert_eq(4, sudoku_grid->max_digit, "Max digit expected to be 4.");
    cr_assert_eq(16, sudoku_grid->size, "Size (squares) expected to be 16.");
    cr_assert_eq(64, sudoku_grid->n_restrictions, "N restrictions expected to be 64.");
    cr_assert_eq(64, sudoku_grid->grid->n_cols, "DLX grid cols expected to be 64.");
    cr_assert_eq(64, sudoku_grid->grid->n_rows, "DLX grid rows expected to be 64.");
}


Test(test_sudoku_grid, sudoku_properties_test_givens_2x2, .fini=teardown)
{
    char *puzzle_str = "1002000004300000";
    sudoku_grid = new_sudoku_grid(puzzle_str);

    cr_assert_eq(2, sudoku_grid->dim);
    cr_assert_eq(4, sudoku_grid->max_digit);
    cr_assert_eq(16, sudoku_grid->size);
    cr_assert_eq(64, sudoku_grid->n_restrictions);
    cr_assert_eq(64, sudoku_grid->grid->n_cols);
    cr_assert_eq(52, sudoku_grid->grid->n_rows);
}


Test(test_sudoku_grid, sudoku_properties_test_empty_3x3, .fini=teardown)
{
    char *puzzle_str = "000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    sudoku_grid = new_sudoku_grid(puzzle_str);

    cr_assert_eq(3, sudoku_grid->dim);
    cr_assert_eq(9, sudoku_grid->max_digit);
    cr_assert_eq(81, sudoku_grid->size);
    cr_assert_eq(324, sudoku_grid->n_restrictions);
    cr_assert_eq(324, sudoku_grid->grid->n_cols);
    cr_assert_eq(729, sudoku_grid->grid->n_rows);
}


Test(test_sudoku_grid, sudoku_properties_test_givens_3x3, .fini=teardown)
{
    char *puzzle_str = "006700100000004078105000000004000037030409050000060020800030010000051000000007209";
    sudoku_grid = new_sudoku_grid(puzzle_str);

    cr_assert_eq(3, sudoku_grid->dim);
    cr_assert_eq(9, sudoku_grid->max_digit);
    cr_assert_eq(81, sudoku_grid->size);
    cr_assert_eq(324, sudoku_grid->n_restrictions);
    cr_assert_eq(324, sudoku_grid->grid->n_cols);
    cr_assert_eq(25 + (81-25)*9, sudoku_grid->grid->n_rows);
}
