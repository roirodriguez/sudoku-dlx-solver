from math import sqrt
from .. import dlx_solver as dlx

class SudokuPuzzle:
    def __init__(self, puzzle):
        _puzzle = puzzle if isinstance(puzzle, list) else SudokuPuzzle.parse_sudoku_str(puzzle)
        self.size = len(_puzzle)
        self.max_digit = int(sqrt(self.size))
        assert self.max_digit**2 == self.size
        self.dim = int(sqrt(self.max_digit))
        assert self.dim**2 == self.max_digit
        self.n_rows = self.max_digit
        self.n_cols = self.max_digit      
        self.grid = self._build_sudoku_grid(_puzzle)

    def _build_sudoku_grid(self, puzzle):
        # Create dlx grid
        grid = dlx.Grid(n_rows = self.n_rows * self.size, n_cols = 4 * self.size)
        # keep track of last upper inserted nodes by col
        upper_nodes = list(grid.cols)
        # function to insert nodes sequentially ordered by cell index
        def _insert_nodes(cell_idx, value):
            (sudoku_row, sudoku_col) = cell_idx // self.max_digit, cell_idx % self.max_digit
            sudoku_block = self.dim * (sudoku_row // self.dim) + sudoku_col // self.dim
            dlx_row_idx = cell_idx * self.max_digit + value - 1
            digit_constraint_col_idx = cell_idx
            row_constraint_col_idx = self.size + self.max_digit * sudoku_row + value - 1
            col_constraint_col_idx = 2 * self.size + self.max_digit * sudoku_col + value - 1
            block_constraint_col_idx = 3 * self.size + self.max_digit * sudoku_block + value - 1
            nodes = [
                dlx.Node(row=dlx_row_idx, col=digit_constraint_col_idx),
                dlx.Node(row=dlx_row_idx, col=row_constraint_col_idx),
                dlx.Node(row=dlx_row_idx, col=col_constraint_col_idx),
                dlx.Node(row=dlx_row_idx, col=block_constraint_col_idx)
            ]
            # link row
            nodes[0].right = nodes[1]
            nodes[1].left = nodes[0]
            nodes[1].right = nodes[2]
            nodes[2].left = nodes[1]
            nodes[2].right = nodes[3]
            nodes[3].left = nodes[2]
            nodes[3].right = nodes[0]
            nodes[0].left = nodes[3]
            # link cols
            nodes[0].up = upper_nodes[nodes[0].col]
            upper_nodes[nodes[0].col].down = nodes[0]
            nodes[1].up = upper_nodes[nodes[1].col]
            upper_nodes[nodes[1].col].down = nodes[1]
            nodes[2].up = upper_nodes[nodes[2].col]
            upper_nodes[nodes[2].col].down = nodes[2]
            nodes[3].up = upper_nodes[nodes[3].col]
            upper_nodes[nodes[3].col].down = nodes[3]
            # update upper nodes
            upper_nodes[nodes[0].col] = nodes[0]
            upper_nodes[nodes[1].col] = nodes[1]
            upper_nodes[nodes[2].col] = nodes[2]
            upper_nodes[nodes[3].col] = nodes[3]
            # setup column links
            nodes[0].column = grid.cols[nodes[0].col]
            nodes[1].column = grid.cols[nodes[1].col]
            nodes[2].column = grid.cols[nodes[2].col]
            nodes[3].column = grid.cols[nodes[3].col]
        for i, val in enumerate(puzzle):
            if val > 0 and val <= self.max_digit:
                # given digit
                _insert_nodes(i, val)
            else:
                for k in range(1, self.max_digit+1):
                    _insert_nodes(i, k)
        # finish column linking
        for i, node in enumerate(upper_nodes):
            node.down = grid.cols[i]
            grid.cols[i].up = node
        return grid

    def print_sudoku_grid_from_solution(self):
        solution = self.get_sudoku_grid_from_dlx_solution()
        block_separator = ("+-" + "--" * self.dim) * self.dim + "+"
        # print solution array
        print(block_separator)
        for i, row in enumerate(solution):
            print("| ", end='')
            for j, val in enumerate(row):
                print(f"{val} ", end='')
                if j % self.dim == self.dim - 1:
                    print("| ", end='')
            print("")
            if i % self.dim == self.dim - 1:
                print(block_separator)

    def get_sudoku_grid_from_dlx_solution(self):
        solution_mat = [[0 for _ in range(self.max_digit)] for _ in range(self.max_digit)]
        for rownode in self.grid.get_solution_status():
            cell_idx = rownode.row // self.max_digit
            (sudoku_row, sudoku_col) = cell_idx // self.max_digit, cell_idx % self.max_digit
            digit = rownode.row - cell_idx * self.max_digit + 1
            solution_mat[sudoku_row][sudoku_col] = digit
            for node in rownode.right_iterator():
                cell_idx = node.row // self.max_digit
                (sudoku_row, sudoku_col) = cell_idx // self.max_digit, cell_idx % self.max_digit
                digit = node.row - cell_idx * self.max_digit + 1
                solution_mat[sudoku_row][sudoku_col] = digit
        return solution_mat

    @staticmethod
    def parse_sudoku_str(sudoku_str):
        # just return string as int array, assertions are made in build_sudoku_grid
        return [int(x) for x in sudoku_str]
