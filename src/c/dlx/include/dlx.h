#ifndef _DLX_H
#define _DLX_H

#include <stdbool.h>

typedef unsigned short dlx_size_t;

#define DIM             ((dlx_size_t) 3)
#define MAX_DIGIT       ((dlx_size_t) DIM*DIM)
#define SIZE            ((dlx_size_t) MAX_DIGIT*MAX_DIGIT)
#define N_RESTRICTIONS  ((dlx_size_t) 4 * SIZE)


struct Node {
    struct Node *up;
    struct Node *down;
    struct Node *right;
    struct Node *left;
    struct Node *column;
    dlx_size_t dlx_column_idx;
    dlx_size_t size;
};


struct DlxSolutionItem {
    struct Node *solution;
    struct DlxSolutionItem *next;
    struct DlxSolutionItem *prev;
};


struct Grid {
    struct Node *root;
    struct DlxSolutionItem *solution_first;
    struct DlxSolutionItem *solution_last;
};

struct Node *create_empty_node(void);
void cover(struct Node *column);
void uncover(struct Node *column);
struct Node *choose_column(struct Node *root_node);
struct Node *choose_grid_column(struct Grid *grid);
void append_solution(struct Grid *grid, struct Node *row);
void pop_solution(struct Grid *grid);
bool search(struct Grid *grid, void (*sol_callback)(void));
void free_dlx_grid(struct Grid *);

#endif