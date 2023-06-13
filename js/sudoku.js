class SudokuCell {
    constructor(value) {
        this.marks = new Set()
        this.value = value
    }

    setMark(number) {
        if (this.value === undefined) {
            this.marks.add(number)
        }
    }

    removeMark(number) {
        if (this.value === undefined && this.marks.size > 1) {
            this.marks.delete(number)
        }
    }

    getMarks() {
        return this.marks.values()
    }

    getValue() {
        return this.value
    }

    setValue() {
        if (this.marks.size == 1) {
            this.value = this.marks.entries()[0]
            this.marks = new Set() // empty set
        }
    }
}

class SudokuGrid {
    constructor() {
        this.grid = [
            // row 1
            new SudokuCell(), new SudokuCell(), new SudokuCell(1),
            new SudokuCell(6), new SudokuCell(), new SudokuCell(8),
            new SudokuCell(), new SudokuCell(), new SudokuCell(),
            // row 2
            new SudokuCell(), new SudokuCell(), new SudokuCell(),
            new SudokuCell(1), new SudokuCell(), new SudokuCell(),
            new SudokuCell(), new SudokuCell(3), new SudokuCell(),
            // row 3
            new SudokuCell(), new SudokuCell(), new SudokuCell(3),
            new SudokuCell(), new SudokuCell(), new SudokuCell(4),
            new SudokuCell(), new SudokuCell(), new SudokuCell(8),
            // row 4
            new SudokuCell(), new SudokuCell(), new SudokuCell(5),
            new SudokuCell(), new SudokuCell(1), new SudokuCell(),
            new SudokuCell(6), new SudokuCell(), new SudokuCell(),
            // row 5
            new SudokuCell(), new SudokuCell(), new SudokuCell(6),
            new SudokuCell(), new SudokuCell(), new SudokuCell(3),
            new SudokuCell(), new SudokuCell(2), new SudokuCell(),
            // row 6
            new SudokuCell(), new SudokuCell(), new SudokuCell(),
            new SudokuCell(), new SudokuCell(), new SudokuCell(9),
            new SudokuCell(5), new SudokuCell(), new SudokuCell(),
            // row 7
            new SudokuCell(), new SudokuCell(9), new SudokuCell(4),
            new SudokuCell(8), new SudokuCell(), new SudokuCell(),
            new SudokuCell(), new SudokuCell(), new SudokuCell(5),
            // row 8
            new SudokuCell(), new SudokuCell(8), new SudokuCell(),
            new SudokuCell(), new SudokuCell(), new SudokuCell(7),
            new SudokuCell(4), new SudokuCell(6), new SudokuCell(),
            // row 9
            new SudokuCell(3), new SudokuCell(), new SudokuCell(),
            new SudokuCell(), new SudokuCell(), new SudokuCell(),
            new SudokuCell(), new SudokuCell(), new SudokuCell()           
        ]
    }

    getCell(row, column) {
        let position = this.#getCellPosition(row, column)
        return this.grid[position]
    }

    #getCellPosition(row, column) {
        return (row-1)*9 + column - 1
    }

    // Para mañana, mejor: implementar Bloque, traer numero de bloque, traer bloque por numero
    // y también retornar iteradores para fila, columna y bloque
    getCellBlockIterator(row, column) {
        let cellPosition = this.#getCellPosition(row, column)
        let cellBlockRowShift = (row-1)%3
        let cellBlockColumnShift = (column-1)%3
        let firstCellInBlockPosition = cellPosition - 10*cellBlockColumnShift - cellBlockRowShift
        let blockPositions = [firstCellInBlockPosition, firstCellInBlockPosition+1, firstCellInBlockPosition+2] // completar
        return blockPositions // substituir por iterador
    }

    getCellRowIterator(row, column) {
        let firstCellInRowPosition = this.#getCellPosition(row, 1)
        return  [firstCellInRowPosition, firstCellInRowPosition+1, firstCellInRowPosition+2] // completar y substittuir por iterador
    }

    getCellColumnIterator(row, column) {
        let firstCellInColumnPosition = this.#getCellPosition(row, 1)
        return  [firstCellInColumnPosition, firstCellInColumnPosition+1, firstCellInColumnPosition+2] // completar y substittuir por iterador
    }

    getCellNeighborsIterator(row, column) {
        const { rowIter, colIter, blkIter } = this.#combineIterators(
            this.getCellBlockIterator(row, column),
            this.getCellRowIterator(row, column),
            this.getCellColumnIterator(row, column)
        )
    }

    getSudokuIterator() {
        return [] // TODO
    }

    #combineIterators(iter1, iter2, iter3) {
        return undefined // TODO
    }
}

class SudokuUtil {
    static printSudokuGrid(grid, printPencilmarks = false) {
        // 1. Crear grid pdf o html con sudoku básico (sin pencilmarks)
        // 2. Implementar a continuación:
        if (printPencilmarks) {

        }
        
    }

    static buildSudokuGrid(initialDigitsStr) {
        // TODO: factory aquí, constructor en SudokuGrid privado
        let grid = new SudokuGrid()
        // Parsear entrada
        return grid
    }
}

let test = new SudokuGrid()
console.log(test.getCell(9, 1))