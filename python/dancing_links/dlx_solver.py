import sys


_MAX_INT = sys.maxsize


class Node:
    def __init__(self, row=None, col=None, name=None):
        self.up = None
        self.down = None
        self.left = None
        self.right = None
        self.name = name
        self.column = None
        self.size = 0
        self.row = row
        self.col = col

    def right_iterator(self):
        right = self.right
        while right != self:
            yield right
            right = right.right

    def left_iterator(self):
        left = self.left
        while left != self:
            yield left
            left = left.left

    def down_iterator(self):
        down = self.down
        while down != self:
            yield down
            down = down.down

    def up_iterator(self):
        up = self.up
        while up != self:
            yield up
            up = up.up


class Grid:
    def __init__(self, n_rows, n_cols, colnames=None):
        self._exact_cover_solution = []
        self.n_rows = n_rows
        self.n_cols = n_cols
        self.solution_listeners = []
        self.colnames = colnames if colnames else list(range(1, n_cols+1))
        # create header
        self.root = Node()
        last_node = self.root
        colnodes = [self.root]
        for colname in self.colnames:
            col = Node(name=colname)
            col.column = col
            col.left = last_node
            last_node.right = col
            last_node = col
            colnodes.append(col)
        self.root.left = colnodes[-1]
        self.cols = list(colnodes[1:])
        # add row indexers, just for initial node inserting purposes
        colnodes[-1].right = self.root 

    @staticmethod
    def cover(col: Node):
        (right, left) = col.right, col.left
        right.left = left
        left.right = right
        for node in col.down_iterator():
            for row_node in node.right_iterator():
                (up, down) = row_node.up, row_node.down
                up.down = down
                down.up = up
                row_node.column.size -= 1

    @staticmethod
    def uncover(col: Node):
        for node in col.up_iterator():
            for row_node in node.left_iterator():
                (up, down) = row_node.up, row_node.down
                up.down = row_node
                down.up = row_node
                row_node.column.size += 1
        (right, left) = col.right, col.left
        left.right = col
        right.left = col

    def choose_column(self):
        """
        Go for minimum branching, this is choosing the column with less size.
        """
        min_size = _MAX_INT
        min_col = None
        for col in self.root.right_iterator():
            if col.size < min_size:
                min_size = col.size
                min_col = col
        return min_col

    def search(self, k=0):
        #print(f"test at k={k}")
        if self.root.right == self.root:
            for listen in self.solution_listeners:
                listen(self)
            return True
        column = self.choose_column()
        Grid.cover(column)
        for r in column.down_iterator():
            self._exact_cover_solution.append(r)
            for j in r.right_iterator():
                Grid.cover(j.column)
            self.search(k+1)
            self._exact_cover_solution.pop()
            for j in r.left_iterator():
                Grid.uncover(j.column)
        Grid.uncover(column)
        return False

    def get_solution_status(self):
        return self._exact_cover_solution
