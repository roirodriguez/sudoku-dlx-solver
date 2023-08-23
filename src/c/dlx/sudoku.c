#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "dlx.h"
#include "sudoku.h"


struct Node *_insert_row(dlx_size_t cell_idx, dlx_size_t value, struct SudokuGrid *sudoku_grid, 
                           struct Node **upper_nodes);
dlx_size_t _calc_dim(char *str_puzzle);


struct SudokuGrid *new_sudoku_grid (char *puzzle_str)
{
    dlx_size_t dim = _calc_dim(puzzle_str);
    if (dim > _MAX_DIMENSION)
    {
        perror("Dimension not supported.");
        exit(EXIT_FAILURE);
    }
    
    struct SudokuGrid *sudoku_grid = malloc(sizeof(struct SudokuGrid));
    sudoku_grid->dim = dim;
    sudoku_grid->max_digit = dim * dim;
    sudoku_grid->size = sudoku_grid->max_digit * sudoku_grid->max_digit;
    sudoku_grid->n_restrictions = sudoku_grid->size * 4;
    sudoku_grid->_malloced_node_ptrs = new_node_list(sudoku_grid->max_digit * sudoku_grid->size);
    sudoku_grid->grid = new_grid(sudoku_grid->n_restrictions);

    struct Grid *grid = sudoku_grid->grid;

    /* 
     * Insert nodes parsing from puzzle_str, one row at a time. upper_nodes helps
     * keeping track of last vertical inserted nodes.
     */
    struct Node **upper_nodes = malloc(sudoku_grid->n_restrictions * sizeof(struct Node *));
    dlx_size_t i;
    for (i=0; i<sudoku_grid->n_restrictions; i++)
    {
        upper_nodes[i] = &(grid->cols[i]);
    }

    for (i = 0; i < sudoku_grid->size; i++) // i = cell index
    {
        if(isdigit(puzzle_str[i]) && (puzzle_str[i] - 48) != 0) // 48 is ascii for 0
        {
            dlx_size_t value = puzzle_str[i] - 48;
            _insert_row(i, value, sudoku_grid, upper_nodes);
            // when inserting a given respect the fact that next inserted row
            // will skip 3 more rows in dlx_row_idx. important for booleanmatrix repr
            // and for api consistency.
            grid->n_rows += 4;
        }
        else
        {
            for (dlx_size_t j=1; j<=sudoku_grid->max_digit; j++)
            {
                _insert_row(i, j, sudoku_grid, upper_nodes);
                grid->n_rows++;
            }
        }
    }

    /* 
     * Finish column linking: _insert_nodes modified upper_nodes to contain here
     * the last inserted node by column.
     */
    for (i=0; i<sudoku_grid->n_restrictions; i++)
    {
        upper_nodes[i]->down = &(grid->cols[i]);
        grid->cols[i].up = upper_nodes[i];
    }

    return sudoku_grid;
}


struct Node *_insert_row(dlx_size_t cell_idx, dlx_size_t value, struct SudokuGrid *sudoku_grid, 
                           struct Node **upper_nodes)
{
    dlx_size_t dlx_row_idx = cell_idx * sudoku_grid->max_digit + value - 1; // static, works because called sequentiallly
    dlx_size_t dim = sudoku_grid->dim, size = sudoku_grid->size, max_digit = sudoku_grid->max_digit;
    dlx_size_t sudoku_row, sudoku_col, sudoku_block;
    sudoku_row = cell_idx / max_digit;
    sudoku_col = cell_idx % max_digit;
    sudoku_block = dim * (sudoku_row / dim) + sudoku_col / dim;  
    int i;

    // 4 restrictions (1 digit/cell, row, col and block), so we need 4 nodes
    struct Node *nodes;
    nodes = calloc(4, sizeof(struct Node));
    sudoku_grid->_malloced_node_ptrs->list[dlx_row_idx] = nodes;

    nodes[0].dlx_column_idx = cell_idx; // so nodes[0] is the cell constraint
    nodes[1].dlx_column_idx = size + max_digit * sudoku_row + value - 1; // row constraint
    nodes[2].dlx_column_idx = 2*size + max_digit * sudoku_col + value - 1; // col constraint
    nodes[3].dlx_column_idx = 3*size + max_digit * sudoku_block + value - 1; // block constraint
    nodes[0].dlx_row_idx = dlx_row_idx;
    nodes[1].dlx_row_idx = dlx_row_idx;
    nodes[2].dlx_row_idx = dlx_row_idx;
    nodes[3].dlx_row_idx = dlx_row_idx;    

    // link row
    nodes[0].right = &(nodes[1]);
    nodes[1].left = &(nodes[0]);
    nodes[1].right = &(nodes[2]);
    nodes[2].left = &(nodes[1]);
    nodes[2].right = &(nodes[3]);
    nodes[3].left = &(nodes[2]);
    nodes[3].right = &(nodes[0]);
    nodes[0].left = &(nodes[3]);

    // link cols
    nodes[0].up = upper_nodes[nodes[0].dlx_column_idx];
    upper_nodes[nodes[0].dlx_column_idx]->down = &(nodes[0]);
    nodes[1].up = upper_nodes[nodes[1].dlx_column_idx];
    upper_nodes[nodes[1].dlx_column_idx]->down = &(nodes[1]); 
    nodes[2].up = upper_nodes[nodes[2].dlx_column_idx];
    upper_nodes[nodes[2].dlx_column_idx]->down = &(nodes[2]);
    nodes[3].up = upper_nodes[nodes[3].dlx_column_idx];
    upper_nodes[nodes[3].dlx_column_idx]->down = &(nodes[3]);

    // update upper nodes
    upper_nodes[nodes[0].dlx_column_idx] = &(nodes[0]);
    upper_nodes[nodes[1].dlx_column_idx] = &(nodes[1]);
    upper_nodes[nodes[2].dlx_column_idx] = &(nodes[2]);
    upper_nodes[nodes[3].dlx_column_idx] = &(nodes[3]);

    // update column linking
    struct Node *cols = sudoku_grid->grid->cols;
    nodes[0].column = &(cols[nodes[0].dlx_column_idx]);
    cols[nodes[0].dlx_column_idx].size++;
    nodes[1].column = &(cols[nodes[1].dlx_column_idx]);
    cols[nodes[1].dlx_column_idx].size++;
    nodes[2].column = &(cols[nodes[2].dlx_column_idx]);
    cols[nodes[2].dlx_column_idx].size++;
    nodes[3].column = &(cols[nodes[3].dlx_column_idx]);
    cols[nodes[3].dlx_column_idx].size++;
}


void free_sudoku_grid(struct SudokuGrid *sudoku_grid)
{
    free_grid(sudoku_grid->grid);
    // free nodes
    for (int i=0; i<sudoku_grid->_malloced_node_ptrs->size; i++)
    {
        struct Node *free_ptr = sudoku_grid->_malloced_node_ptrs->list[i];
        if (free_ptr == NULL)
            break;
        free(free_ptr);
    }
    free_node_list(sudoku_grid->_malloced_node_ptrs);
    free(sudoku_grid);
}


dlx_size_t _calc_dim(char *str_puzzle)
{
    dlx_size_t size = (dlx_size_t) strlen(str_puzzle);
    dlx_size_t i;
    for (i=0; i<_MAX_DIMENSION+1; i++)
    {
        if (i*i*i*i == size)
            break;
    }
    return i;
}


void search_solution_printing_callback(struct Grid *solved_grid)
{
    struct NodeStackItem *stack_ptr = solved_grid->solution_stack->top;
    /* TODO: This isn't good, i need to know here dim and size of the sudoku i just solved. Look for a better solution. */
    dlx_size_t value, cellidx, size = solved_grid->n_cols / 4;
    char *solution = malloc(size * sizeof(char) + 1);
    solution[size] = '\0';
    while(stack_ptr != NULL)
    {
        /* dlx row num gives us cell and value */
        cellidx = stack_ptr->data_ptr->dlx_row_idx / 4;
        value = 1 + stack_ptr->data_ptr->dlx_row_idx % 4;
        solution[cellidx] = 48 + value;
        stack_ptr = stack_ptr->prev;
    }
    puts(solution);
}