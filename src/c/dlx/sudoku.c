#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dlx.h"
#include "sudoku.h"

void _insert_nodes(dlx_size_t cell_idx, dlx_size_t value,
                    struct Node **upper_nodes, struct Node **grid_cols);

struct Grid *create_sudoku_grid (char *puzzle_str)
{
    struct Grid *grid = malloc(sizeof(struct Grid *));
    grid = calloc(1, sizeof(struct Grid));
    struct Node **cols = malloc(N_RESTRICTIONS * sizeof(struct Node **));

    /* Create header (column indexes) */
    struct Node *root = create_empty_node();
    grid->root = root;
    cols[0] = create_empty_node();
    root->right = cols[0];
    cols[0]->left = root;
    for (dlx_size_t i=1; i<N_RESTRICTIONS; i++)
    {
        cols[i] = create_empty_node();
        cols[i]->left = cols[i-1];
        cols[i-1]->right = cols[i];
    }
    cols[N_RESTRICTIONS-1]->right = root;
    root->left = cols[N_RESTRICTIONS-1];

    /* 
     * Insert nodes parsing from puzzle_str, one row at a time. upper_nodes helps
     * keeping track of last vertical inserted nodes.
     */
    struct Node **upper_nodes = malloc(N_RESTRICTIONS * sizeof(struct Node **));
    memcpy(upper_nodes, cols, N_RESTRICTIONS * sizeof(*cols));
    //upper_nodes = cols;
    dlx_size_t i, j, k;
    for (i=0; i<SIZE; i++) // i = cell index
    {
        for (j=0; j<MAX_DIGIT; j++) // j = value - 1
        {
            dlx_size_t value;
            if(isdigit(puzzle_str[i]) && (value = puzzle_str[i] - 48) != 0) // 48 is ascii for 0
                _insert_nodes(i, value, upper_nodes, cols);
            else
                for (k=1; k<=MAX_DIGIT; k++)
                    _insert_nodes(i, k,  upper_nodes, cols);
        }
    }

    /* 
     * Finish column linking: _insert_nodes modified upper_nodes to contain here
     * the last inserted node by column.
     */
    for (i=0; i<N_RESTRICTIONS; i++)
    {
        upper_nodes[i]->down = cols[i];
        cols[i]->up = upper_nodes[i];
    }

    return grid;
}

void _insert_nodes(dlx_size_t cell_idx, dlx_size_t value,
                    struct Node **upper_nodes, struct Node **grid_cols)
{
    dlx_size_t sudoku_row, sudoku_col, sudoku_block;
    sudoku_row = cell_idx / MAX_DIGIT;
    sudoku_col = cell_idx % MAX_DIGIT;
    sudoku_block = DIM * (sudoku_row / DIM) + sudoku_col % DIM;  
    int i;

    // 4 restrictions (1 digit/cell, row, col and block), so we need 4 nodes
    struct Node **nodes;
    nodes = calloc(4, sizeof(struct Node **));
    nodes[0] = create_empty_node();
    nodes[0]->dlx_column_idx = cell_idx; // so nodes[0] is the cell constraint
    nodes[1] = create_empty_node();
    nodes[1]->dlx_column_idx = SIZE + MAX_DIGIT * sudoku_row + value - 1; // row constraint
    nodes[2] = create_empty_node();
    nodes[2]->dlx_column_idx = 2*SIZE + MAX_DIGIT * sudoku_col + value - 1; // col constraint
    nodes[3] = create_empty_node();
    nodes[3]->dlx_column_idx = 3*SIZE + MAX_DIGIT * sudoku_block + value - 1; // block constraint        

    // link row
    nodes[0]->right = nodes[1];
    nodes[1]->left = nodes[0];
    nodes[1]->right = nodes[2];
    nodes[2]->left = nodes[1];
    nodes[2]->right = nodes[3];
    nodes[3]->left = nodes[2];
    nodes[3]->right = nodes[0];
    nodes[0]->left = nodes[3];

    // link cols
    nodes[0]->up = upper_nodes[nodes[0]->dlx_column_idx];
    upper_nodes[nodes[0]->dlx_column_idx]->down = nodes[0];
    nodes[1]->up = upper_nodes[nodes[1]->dlx_column_idx];
    upper_nodes[nodes[1]->dlx_column_idx]->down = nodes[1]; 
    nodes[2]->up = upper_nodes[nodes[2]->dlx_column_idx];
    upper_nodes[nodes[2]->dlx_column_idx]->down = nodes[2];
    nodes[3]->up = upper_nodes[nodes[3]->dlx_column_idx];
    upper_nodes[nodes[3]->dlx_column_idx]->down = nodes[3];

    // update upper nodes
    upper_nodes[nodes[0]->dlx_column_idx] = nodes[0];
    upper_nodes[nodes[1]->dlx_column_idx] = nodes[1];
    upper_nodes[nodes[2]->dlx_column_idx] = nodes[2];
    upper_nodes[nodes[3]->dlx_column_idx] = nodes[3];

    // update column linking
    nodes[0]->column = grid_cols[nodes[0]->dlx_column_idx];
    grid_cols[nodes[0]->dlx_column_idx]->size++;
    nodes[1]->column = grid_cols[nodes[1]->dlx_column_idx];
    grid_cols[nodes[1]->dlx_column_idx]->size++;
    nodes[2]->column = grid_cols[nodes[2]->dlx_column_idx];
    grid_cols[nodes[2]->dlx_column_idx]->size++;
    nodes[3]->column = grid_cols[nodes[3]->dlx_column_idx];
    grid_cols[nodes[3]->dlx_column_idx]->size++;
}

void sudoku_solution_printing_callback(void)
{

}