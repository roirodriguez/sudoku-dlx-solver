#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <stdlib.h>
#include "dlx.h"
#include "dlx_util.h"
#include "util/test_data.h"


struct Grid *grid = NULL;
struct SolutionList *solution_lst = NULL;


void _setup()
{
    solution_lst = new_solution_list(10);
}


void teardown()
{
    free_knut_paper_basic_grid(grid);
    free_solution_list(solution_lst);
}


Test(test_dlx_search, search_test_no_solution, .init=setup_nosol, .fini=teardown)
{

}
