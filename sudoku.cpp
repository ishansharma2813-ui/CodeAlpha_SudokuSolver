// CodeAlpha C++ Internship - Task 3: Sudoku Solver
// Approach: 2D array grid + recursive backtracking.
// Before placing a number we check row, column and 3x3 subgrid rules.

#include <iostream>
#include <string>
#include <array>

using namespace std;

const int N = 9;
using Grid = array<array<int, N>, N>;

// Print the grid with separators for 3x3 boxes.
void printGrid(const Grid& g) {
    for (int r = 0; r < N; r++) {
        if (r % 3 == 0) cout << "+-------+-------+-------+\n";
        for (int c = 0; c < N; c++) {
            if (c % 3 == 0) cout << "| ";
            if (g[r][c] == 0) cout << ". ";
            else cout << g[r][c] << " ";
        }
        cout << "|\n";
    }
    cout << "+-------+-------+-------+\n";
}

// Sudoku rule check: can `num` be placed at (row, col)?
bool isSafe(const Grid& g, int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (g[row][i] == num) return false;  // row
        if (g[i][col] == num) return false;  // column
    }
    int boxRow = row - row % 3;
    int boxCol = col - col % 3;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (g[boxRow + r][boxCol + c] == num) return false;  // 3x3 box
    return true;
}

// Backtracking: find an empty cell, try 1-9, recurse, undo if stuck.
bool solve(Grid& g) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (g[row][col] != 0) continue;
            for (int num = 1; num <= 9; num++) {
                if (isSafe(g, row, col, num)) {
                    g[row][col] = num;
                    if (solve(g)) return true;
                    g[row][col] = 0;  // backtrack
                }
            }
            return false;  // no number fits here
        }
    }
    return true;  // no empty cell left -> solved
}

// Check that the numbers the user typed do not already break the rules.
bool isInitialGridValid(Grid& g) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            int v = g[r][c];
            if (v == 0) continue;
            g[r][c] = 0;
            bool ok = isSafe(g, r, c, v);
            g[r][c] = v;
            if (!ok) return false;
        }
    }
    return true;
}

// Read 9 rows of 9 digits (0 or . = empty).
bool readGrid(Grid& g) {
    cout << "\nEnter 9 rows, each with 9 digits (use 0 for empty cells).\n";
    cout << "Example row: 530070000\n\n";
    for (int r = 0; r < N; r++) {
        string line;
        while (true) {
            cout << "Row " << r + 1 << ": ";
            if (!(cin >> line)) return false;  // input closed
            bool valid = line.size() == N;
            for (char ch : line)
                if (!((ch >= '0' && ch <= '9') || ch == '.')) valid = false;
            if (valid) break;
            cout << "  Invalid! Type exactly 9 characters (digits 0-9).\n";
        }
        for (int c = 0; c < N; c++)
            g[r][c] = (line[c] == '.') ? 0 : line[c] - '0';
    }
    return true;
}

Grid samplePuzzle() {
    return {{
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    }};
}

int main() {
    cout << "=====================================\n";
    cout << "        SUDOKU SOLVER (C++)          \n";
    cout << "=====================================\n";
    cout << "1. Enter my own puzzle\n";
    cout << "2. Solve the sample puzzle\n";
    cout << "Choose (1/2): ";

    int choice;
    if (!(cin >> choice)) return 1;

    Grid grid{};
    if (choice == 1) {
        if (!readGrid(grid)) return 1;
    } else {
        grid = samplePuzzle();
    }

    cout << "\nPuzzle:\n";
    printGrid(grid);

    if (!isInitialGridValid(grid)) {
        cout << "\nThis puzzle breaks Sudoku rules (duplicate in a row, column or box).\n";
        return 0;
    }

    if (solve(grid)) {
        cout << "\nSolved:\n";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for this puzzle.\n";
    }
    return 0;
}
