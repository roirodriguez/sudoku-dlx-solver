#include <criterion/criterion.h>
#include "dlx.h"
#include "util/knut_paper_data.h"


struct Grid *grid;


void setup()
{
    grid = new_grid((dlx_size_t) 5);
}


void teardown()
{
    free_grid(grid);
}


Test(test_grid_creation, new_grid_test, .init=setup, .fini=teardown)
{

}
