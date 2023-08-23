#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlx.h"
#include "dlx_util.h"


struct Grid *get_knut_paper_basic_grid(void)
{
    struct Grid *grid = new_grid(7);
    grid->n_rows = 6;
    struct Node *nodes = calloc(16, sizeof(struct Node));
    
    // Manually connect nodes
    nodes[0].dlx_row_idx = 0;
    nodes[0].right = &nodes[1];
    nodes[0].left = &nodes[2];
    nodes[0].column = &(grid->cols[2]);
    nodes[0].up = &(grid->cols[2]);
    nodes[0].down = &nodes[7];
    nodes[0].dlx_column_idx = 2;

    nodes[1].dlx_row_idx = 0;
    nodes[1].right = &nodes[2];
    nodes[1].left = &nodes[0];
    nodes[1].column = &(grid->cols[4]);
    nodes[1].up = &(grid->cols[4]);
    nodes[1].down = &nodes[14];
    nodes[1].dlx_column_idx = 4;

    nodes[2].dlx_row_idx = 0;
    nodes[2].right = &nodes[0];
    nodes[2].left = &nodes[1];
    nodes[2].column = &(grid->cols[5]);
    nodes[2].up = &(grid->cols[5]);
    nodes[2].down = &nodes[8];
    nodes[2].dlx_column_idx = 5;

    nodes[3].dlx_row_idx = 1;
    nodes[3].right = &nodes[4];
    nodes[3].left = &nodes[5];
    nodes[3].column = &(grid->cols[0]);
    nodes[3].up = &(grid->cols[0]);
    nodes[3].down = &nodes[9];
    nodes[3].dlx_column_idx = 0;

    nodes[4].dlx_row_idx = 1;
    nodes[4].right = &nodes[5];
    nodes[4].left = &nodes[3];
    nodes[4].column = &(grid->cols[3]);
    nodes[4].up = &(grid->cols[3]);
    nodes[4].down = &nodes[10];
    nodes[4].dlx_column_idx = 3;

    nodes[5].dlx_row_idx = 1;
    nodes[5].right = &nodes[3];
    nodes[5].left = &nodes[4];
    nodes[5].column = &(grid->cols[6]);
    nodes[5].up = &(grid->cols[6]);
    nodes[5].down = &nodes[12];
    nodes[5].dlx_column_idx = 6;

    nodes[6].dlx_row_idx = 2;
    nodes[6].right = &nodes[7];
    nodes[6].left = &nodes[8];
    nodes[6].column = &(grid->cols[1]);
    nodes[6].up = &(grid->cols[1]);
    nodes[6].down = &nodes[11];
    nodes[6].dlx_column_idx = 1;

    nodes[7].dlx_row_idx = 2;
    nodes[7].right = &nodes[8];
    nodes[7].left = &nodes[6];
    nodes[7].column = &(grid->cols[2]);
    nodes[7].up = &nodes[0];
    nodes[7].down = &(grid->cols[2]);
    nodes[7].dlx_column_idx = 2;

    nodes[8].dlx_row_idx = 2;
    nodes[8].right = &nodes[6];
    nodes[8].left = &nodes[7];
    nodes[8].column = &(grid->cols[5]);
    nodes[8].up = &nodes[2];
    nodes[8].down = &(grid->cols[5]);
    nodes[8].dlx_column_idx = 5;

    nodes[9].dlx_row_idx = 3;
    nodes[9].right = &nodes[10];
    nodes[9].left = &nodes[10];
    nodes[9].column = &(grid->cols[0]);
    nodes[9].up = &nodes[3];
    nodes[9].down = &(grid->cols[0]);
    nodes[9].dlx_column_idx = 0;

    nodes[10].dlx_row_idx = 3;
    nodes[10].right = &nodes[9];
    nodes[10].left = &nodes[9];
    nodes[10].column = &(grid->cols[3]);
    nodes[10].up = &nodes[4];
    nodes[10].down = &nodes[13];
    nodes[10].dlx_column_idx = 3; 

    nodes[11].dlx_row_idx = 4;
    nodes[11].right = &nodes[12];
    nodes[11].left = &nodes[12];
    nodes[11].column = &(grid->cols[1]);
    nodes[11].up = &nodes[6];
    nodes[11].down = &(grid->cols[1]);
    nodes[11].dlx_column_idx = 1;

    nodes[12].dlx_row_idx = 4;
    nodes[12].right = &nodes[11];
    nodes[12].left = &nodes[11];
    nodes[12].column = &(grid->cols[6]);
    nodes[12].up = &nodes[5];
    nodes[12].down = &nodes[15];
    nodes[12].dlx_column_idx = 6;

    nodes[13].dlx_row_idx = 5;
    nodes[13].right = &nodes[14];
    nodes[13].left = &nodes[15];
    nodes[13].column = &(grid->cols[3]);
    nodes[13].up = &nodes[10];
    nodes[13].down = &(grid->cols[3]);
    nodes[13].dlx_column_idx = 3;

    nodes[14].dlx_row_idx = 5;
    nodes[14].right = &nodes[15];
    nodes[14].left = &nodes[13];
    nodes[14].column = &(grid->cols[4]);
    nodes[14].up = &nodes[1];
    nodes[14].down = &(grid->cols[4]);
    nodes[14].dlx_column_idx = 4;

    nodes[15].dlx_row_idx = 5;
    nodes[15].right = &nodes[13];
    nodes[15].left = &nodes[14];
    nodes[15].column = &(grid->cols[6]);
    nodes[15].up = &nodes[12];
    nodes[15].down = &(grid->cols[6]);
    nodes[15].dlx_column_idx = 6;

    // update up/down linking of columns
    grid->cols[0].down = &nodes[3];
    grid->cols[0].up = &nodes[9];
    grid->cols[0].size = 2;
    grid->cols[1].down = &nodes[6];
    grid->cols[1].up = &nodes[11];
    grid->cols[1].size = 2;
    grid->cols[2].down = &nodes[0];
    grid->cols[2].up = &nodes[7];
    grid->cols[2].size = 2;
    grid->cols[3].down = &nodes[4];
    grid->cols[3].up = &nodes[13];
    grid->cols[3].size = 3;
    grid->cols[4].down = &nodes[1];
    grid->cols[4].up = &nodes[14];
    grid->cols[4].size = 2;
    grid->cols[5].down = &nodes[2];
    grid->cols[5].up = &nodes[8];
    grid->cols[5].size = 2;
    grid->cols[6].down = &nodes[5];
    grid->cols[6].up = &nodes[15];
    grid->cols[6].size = 3;    
 
    return grid;
}


struct Grid *get_knut_paper_nosol_grid(void)
{
    struct Grid *grid = get_knut_paper_basic_grid();

    // just remove row 3 (not removing row 0 to keep a ptr to the node memory chunk
    // reserved into the grid).
    struct Node *row_ptr = grid->cols[0].down->down;
    struct Node *first = row_ptr;
    
    // loop does not free because node space was reserved in block, so 
    // removed row will be freed with the rest of the grid by calling
    // free_knut_paper_basic_grid
    do
    {
        row_ptr->down->up = row_ptr->up;
        row_ptr->up->down = row_ptr->down;
        row_ptr->column->size--;
        row_ptr = row_ptr->right;
    } 
    while(first != row_ptr);

    grid->n_rows--;
    
    return grid;
}


struct Grid *get_knut_paper_3sol_grid(void)
{
    struct Grid *grid = get_knut_paper_basic_grid();

    // Add 1 1 1 0 0 1 0 so that is a solution with existing row 6
    struct Node *nodes = calloc(4, sizeof(struct Node));

    nodes[0].column = &(grid->cols[0]);
    nodes[0].dlx_column_idx = 0;
    nodes[0].dlx_row_idx = 6;
    nodes[0].right = &(nodes[1]);
    nodes[0].left = &(nodes[3]);
    nodes[0].up = grid->cols[0].up;
    nodes[0].down = &(grid->cols[0]);
    grid->cols[0].up->down = &(nodes[0]);
    grid->cols[0].up = &(nodes[0]);
    grid->cols[0].size++;

    nodes[1].column = &(grid->cols[1]);
    nodes[1].dlx_column_idx = 1;
    nodes[1].dlx_row_idx = 6;
    nodes[1].right = &(nodes[2]);
    nodes[1].left = &(nodes[0]);
    nodes[1].up = grid->cols[1].up;
    nodes[1].down = &(grid->cols[1]);
    grid->cols[1].up->down = &(nodes[1]);
    grid->cols[1].up = &(nodes[1]);
    grid->cols[1].size++;

    nodes[2].column = &(grid->cols[2]);
    nodes[2].dlx_column_idx = 2;
    nodes[2].dlx_row_idx = 6;
    nodes[2].right = &(nodes[3]);
    nodes[2].left = &(nodes[1]);
    nodes[2].up = grid->cols[2].up;
    nodes[2].down = &(grid->cols[2]);
    grid->cols[2].up->down = &(nodes[2]);
    grid->cols[2].up = &(nodes[2]);
    grid->cols[2].size++;

    nodes[3].column = &(grid->cols[5]);
    nodes[3].dlx_column_idx = 5;
    nodes[3].dlx_row_idx = 6;
    nodes[3].right = &(nodes[0]);
    nodes[3].left = &(nodes[2]);
    nodes[3].up = grid->cols[5].up;
    nodes[3].down = &(grid->cols[5]);
    grid->cols[5].up->down = &(nodes[3]);
    grid->cols[5].up = &(nodes[3]);
    grid->cols[5].size++;
    

    // Add 0 1 1 0 1 1 0 so that is a solution with existing row 2
    nodes = calloc(4, sizeof(struct Node));

    nodes[0].column = &(grid->cols[1]);
    nodes[0].dlx_column_idx = 1;
    nodes[0].dlx_row_idx = 7;
    nodes[0].right = &(nodes[1]);
    nodes[0].left = &(nodes[3]);
    nodes[0].up = grid->cols[1].up;
    nodes[0].down = &(grid->cols[1]);
    grid->cols[1].up->down = &(nodes[0]);
    grid->cols[1].up = &(nodes[0]);
    grid->cols[1].size++;

    nodes[1].column = &(grid->cols[2]);
    nodes[1].dlx_column_idx = 2;
    nodes[1].dlx_row_idx = 7;
    nodes[1].right = &(nodes[2]);
    nodes[1].left = &(nodes[0]);
    nodes[1].up = grid->cols[2].up;
    nodes[1].down = &(grid->cols[2]);
    grid->cols[2].up->down = &(nodes[1]);
    grid->cols[2].up = &(nodes[1]);
    grid->cols[2].size++;

    nodes[2].column = &(grid->cols[4]);
    nodes[2].dlx_column_idx = 4;
    nodes[2].dlx_row_idx = 6;
    nodes[2].right = &(nodes[3]);
    nodes[2].left = &(nodes[1]);
    nodes[2].up = grid->cols[4].up;
    nodes[2].down = &(grid->cols[4]);
    grid->cols[4].up->down = &(nodes[2]);
    grid->cols[4].up = &(nodes[2]);
    grid->cols[4].size++;

    nodes[3].column = &(grid->cols[5]);
    nodes[3].dlx_column_idx = 5;
    nodes[3].dlx_row_idx = 6;
    nodes[3].right = &(nodes[0]);
    nodes[3].left = &(nodes[2]);
    nodes[3].up = grid->cols[5].up;
    nodes[3].down = &(grid->cols[5]);
    grid->cols[5].up->down = &(nodes[3]);
    grid->cols[5].up = &(nodes[3]);
    grid->cols[5].size++;

    grid->n_rows += 2;
    return grid;
}


void free_knut_paper_basic_grid(struct Grid *grid)
{
    // Nodes were allocated with calloc in block, so freeing the first one works
    free(grid->cols[2].down);
    free_grid(grid);
}


void free_knut_paper_3sol_grid(struct Grid *grid)
{
    // free the newly 2 inserted rows
    struct Node *free_ptr1 = grid->cols[0].down->down->down;
    struct Node *free_ptr2 = grid->cols[1].down->down->down->down;
    free(free_ptr1);
    free(free_ptr2);
    // free the rest of the grid
    free_knut_paper_basic_grid(grid);
}


struct BooleanMatrix *get_knut_paper_basic_matrix(void)
{
    struct BooleanMatrix *matrix = new_boolean_matrix(6, 7);
    bool *ptr = calloc(42, sizeof(bool));
    bool data[42] = {
        false, false, true, false, true, true, false,
        true, false, false, true, false, false, true,
        false, true, true, false, false, true, false,
        true, false, false, true, false, false, false,
        false, true, false, false, false, false, true,
        false, false, false, true, true, false, true
    };
    memcpy(ptr, data, 42 * sizeof(bool));
    for(int i=0; i<6; i++)
        matrix->matrix[i] = (ptr + i* 7 * sizeof(bool));
    return matrix;
}


struct BooleanMatrix *get_knut_paper_matrix_col3_covered()
{
    struct BooleanMatrix *matrix = new_boolean_matrix(6, 7);
    bool *ptr = calloc(42, sizeof(bool));
    bool data[42] = {
        false, false, true, false, true, true, false,
        false, false, false, false, false, false, false,
        false, true, true, false, false, true, false,
        false, false, false, false, false, false, false,
        false, true, false, false, false, false, true,
        false, false, false, false, false, false, false
    };
    memcpy(ptr, data, 42 * sizeof(bool));
    for(int i=0; i<6; i++)
        matrix->matrix[i] = (ptr + i* 7 * sizeof(bool));
    return matrix;    
}


struct BooleanMatrix *get_knut_paper_matrix_col35_covered()
{
    struct BooleanMatrix *matrix = new_boolean_matrix(6, 7);
    bool *ptr = calloc(42, sizeof(bool));
    bool data[42] = {
        false, false, false, false, false, false, false,
        false, false, false, false, false, false, false,
        false, false, false, false, false, false, false,
        false, false, false, false, false, false, false,
        false, true, false, false, false, false, true,
        false, false, false, false, false, false, false
    };
    memcpy(ptr, data, 42 * sizeof(bool));
    for(int i=0; i<6; i++)
        matrix->matrix[i] = (ptr + i* 7 * sizeof(bool));
    return matrix;    
}
