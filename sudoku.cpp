#include <stdio.h>

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d", grid[i][j]);
        printf("\n");
    }
}

// Function to check if it's safe to place num at grid[row][col]
int isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return 0;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return 0;
        }
    }

    return 1;
}

// Function to solve the Sudoku puzzle using backtracking
int solveSudoku(int grid[N][N]) {
    int row, col;

    // Find the first empty cell
    int found = 0;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                found = 1;
                break;
            }
        }
        if (found)
            break;
    }

    // If no empty cell is found, the puzzle is solved
    if (!found)
        return 1;

    // Try placing numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recur to try placing the next number
            if (solveSudoku(grid))
                return 1;

            // If placing num doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no number can be placed, backtrack
    return 0;
}

int main() {
    int grid[N][N];

    // Input Sudoku grid from the user
    printf("Enter the Sudoku grid to solve (use 0 for empty cells):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Solve the Sudoku puzzle
    if (solveSudoku(grid)) {
        printf("Solved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
