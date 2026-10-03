# CodeAlpha_SudokuSolver

Console-based Sudoku Solver in C++ built for the **CodeAlpha C++ Programming Internship (Task 3)**.

## How it works
- The grid is a 2D array (9x9). `0` means an empty cell.
- `isSafe()` checks the row, column and 3x3 subgrid rules before placing a number.
- `solve()` uses recursive **backtracking**: find an empty cell, try 1-9, recurse, and undo the move if it leads to a dead end.
- The input puzzle is validated first, so an invalid puzzle is reported instead of looping.

## Run
```bash
g++ -std=c++17 -o sudoku sudoku.cpp
./sudoku
```
Choose `1` to enter your own puzzle (9 rows of 9 digits, `0` for empty) or `2` for the built-in sample.

## Sample output
```
+-------+-------+-------+
| 5 3 4 | 6 7 8 | 9 1 2 |
| 6 7 2 | 1 9 5 | 3 4 8 |
| 1 9 8 | 3 4 2 | 5 6 7 |
...
```

## Author
Ishan Sharma
