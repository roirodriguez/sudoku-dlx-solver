#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <stdlib.h>
#include "dlx.h"
#include "dlx_util.h"
#include "util/test_data_dlx.h"


struct Grid *grid = NULL;
struct SolutionList *solution_lst = NULL;


/* Acummulates dlx search solutions into global var solution_lst */
void solution_callback(struct Grid *solved_grid);


void _setup()
{
    solution_lst = new_solution_list(10);
}

void setup_knut()
{
    _setup();
    grid = get_knut_paper_basic_grid();
}

void setup_nosol()
{
    _setup();
    grid = get_knut_paper_nosol_grid();
}

void setup_multisol()
{
    _setup();
    grid = get_knut_paper_3sol_grid();
}

void teardown()
{
    free_knut_paper_basic_grid(grid);
    free_solution_list(solution_lst);
}

void teardown_multisol()
{
    free_knut_paper_3sol_grid(grid);
    free_solution_list(solution_lst);
}


Test(test_dlx_search, cover_test, .init=setup_knut, .fini=teardown)
{
    cover(&(grid->cols[3]));
    cr_assert(
        check_expected(get_grid_boolean_matrix_repr(grid), get_knut_paper_matrix_col3_covered()),
        "After covering col 3 grid linking is the expected."
    );

    cover(&(grid->cols[5])); 
    cr_assert(
        check_expected(get_grid_boolean_matrix_repr(grid), get_knut_paper_matrix_col35_covered()),
        "After covering col 3 and then 5, grid linking is the expected."
    );

    uncover(&(grid->cols[5]));
    cr_assert(
        check_expected(get_grid_boolean_matrix_repr(grid), get_knut_paper_matrix_col3_covered()),
        "After uncovering col 5, grid linking is the expected"
    );

    uncover(&(grid->cols[3]));
    cr_assert(
        check_expected(get_grid_boolean_matrix_repr(grid), get_knut_paper_basic_matrix()),
        "After uncovering col 3, grid linking is the expected"
    );

    // check: if i cover all columns root points to itself
    cover(&(grid->cols[0]));
    cover(&(grid->cols[1]));
    cover(&(grid->cols[2]));
    cover(&(grid->cols[3]));
    cover(&(grid->cols[4]));
    cover(&(grid->cols[5]));
    cover(&(grid->cols[6]));
    cr_assert_eq(grid->root, grid->root->right, "After covering all cols root points to itself.");
}


Test(test_dlx_search, search_test_unique, .init=setup_knut, .fini=teardown)
{
    search(grid, solution_callback);

    // check only one solution, and solution is an exact cover
    cr_assert_eq(1, solution_lst->used_size, "There is a unique solution.");
    cr_assert(check_exact_cover(grid, solution_lst->list[0]));
}


Test(test_dlx_search, search_test_multi, .init=setup_multisol, .fini=teardown_multisol)
{
    search(grid, solution_callback);

    // check only one solution, and solution is an exact cover
    cr_assert_eq(3, solution_lst->used_size, "There are 3 solutions.");
    for (int i=0; i<solution_lst->used_size; i++)
        cr_assert(check_exact_cover(grid, solution_lst->list[i]));
}


Test(test_dlx_search, search_test_no_solution, .init=setup_nosol, .fini=teardown)
{
    search(grid, solution_callback);

    // check only one solution, and solution is an exact cover
    cr_assert_eq(0, solution_lst->used_size, "There are no solutions.");
}


void solution_callback(struct Grid *solved_grid)
{
    default_solution_callback_template(solved_grid, solution_lst);
}
