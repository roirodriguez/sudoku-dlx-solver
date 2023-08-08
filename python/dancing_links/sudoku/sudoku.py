from argparse import ArgumentParser
from .util import SudokuPuzzle


def parse_args():
    parser = ArgumentParser(description="Sudoku solver using Knut's DLX algorithm.")
    parser.add_argument(
        '--str',
        required=True,
        type=str,
        help="Sudoku givens as 81 (for 3x3, can pass 16 len for 2x2, etc) len string."
    )
    return parser.parse_args()


class SudokuPuzzleSolver(SudokuPuzzle):
    def __init__(self, puzzle):
        super().__init__(puzzle)
        self.solution_count = 0
        self._install_listeners()

    def _install_listeners(self):
        # install print solution listener
        def _print_sol_listener(grid):
            self.print_sudoku_grid_from_solution()
            print()
        self.grid.solution_listeners.append(_print_sol_listener)
        # install solution count listener
        def _solution_count_listener(_):
            self.solution_count += 1
        self.grid.solution_listeners.append(_solution_count_listener)

    def solve(self):
        # solve and get all solutions
        while self.grid.search():
            continue


if __name__ == "__main__":
    conf = parse_args()
    sudoku_puzzle = SudokuPuzzleSolver(puzzle=conf.str)
    sudoku_puzzle.solve()
    print(f"Found {sudoku_puzzle.solution_count} solutions." if sudoku_puzzle.solution_count > 0 else "No solutions found")
