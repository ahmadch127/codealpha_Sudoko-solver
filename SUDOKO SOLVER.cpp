#include <iostream>
using namespace std;

const int N = 9;
int grid[N][N] = {
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}
};

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0 && i != 0)
            cout << "------+-------+------\n";
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            if (grid[i][j] == 0)
                cout << ". ";
            else
                cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}

// Check if placing num in grid[row][col] is valid
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Solve Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid))
                            return true;
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
    return true;
}

int main() {
    cout << "Initial Sudoku Puzzle:\n";
    printGrid(grid);

    char choice;
    do {
        int r, c, val;
        cout << "\nEnter row (1-9), column (1-9), and value (0 to clear): ";
        cin >> r >> c >> val;
        if (r >= 1 && r <= 9 && c >= 1 && c <= 9 && val >= 0 && val <= 9) {
            grid[r - 1][c - 1] = val;
        } else {
            cout << "Invalid input! Try again.\n";
        }

        printGrid(grid);

        cout << "Do you want to enter more values? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\nSolving Sudoku...\n";
    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        cout << "No solution exists!\n";
    }

    return 0;
}
