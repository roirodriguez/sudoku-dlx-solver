#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <stdlib.h>
#include "dlx.h"
#include "dlx_util.h"
#include "util/test_data.h"


struct Grid *grid = NULL;
struct BooleanMatrix **solutions;


/* Acummulates dlx search solutions into global var solutions */
void solution_cum_callback(struct Grid *solved_grid);

/* Search all solutions. Returns number of solutions, BooleanMat solutions given in global var solutions */
int search_all_solutions(struct Grid *grid);


void setup()
{
    grid = get_knut_paper_basic_grid();
    solutions = calloc(10, sizeof(struct BooleanMatrix *));
}


void teardown()
{
    free_grid(grid);
    for(int i=0; i<10; i++)
    {
        if (solutions[i] != NULL)
            free(solutions[i]);
        else
            break;
    }
    free(solutions);
}


Test(test_dlx_search, cover_test, .init=setup, .fini=teardown)
{
    cover(&(grid->cols[3]));
    cr_assert(check_expected(get_grid_boolean_matrix_repr(grid), get_knut_paper_matrix_col3_covered()));


    cover(&(grid->cols[5])); 
    cr_assert(check_expected(get_grid_boolean_matrix_repr(grid), get_knut_paper_matrix_col35_covered()));

    uncover(&(grid->cols[5]));
    cr_assert(check_expected(get_grid_boolean_matrix_repr(grid), get_knut_paper_matrix_col3_covered()));

    uncover(&(grid->cols[3]));
    cr_assert(check_expected(get_grid_boolean_matrix_repr(grid), get_knut_paper_basic_matrix()));
}


Test(test_dlx_search, search_test_unique, .init=setup, .fini=teardown)
{
    int n_solutions = search_all_solutions(grid);

    // check only one solution, and solution is an exact cover
    cr_assert_eq(1, n_solutions, "There is a unique solution.");
    cr_assert(check_exact_cover(solutions[0]));
}


Test(test_dlx_search, search_test_multi, .fini=teardown)
{
    cr_fail("Still not implemented, so failing.");
}


Test(test_dlx_search, search_test_no_solution, .fini=teardown)
{
    cr_fail("Still not implemented, so failing.");
}


void solution_cum_callback(struct Grid *solved_grid)
{
    static int last_sol_idx = 0;
    solutions[last_sol_idx] = get_solution_boolean_matrix_repr(grid);
    last_sol_idx++;
}


int search_all_solutions(struct Grid *grid)
{
    int sol_count = 0;
    while(search(grid, solution_cum_callback))
    {
        sol_count++;
    }
    return sol_count;
}
