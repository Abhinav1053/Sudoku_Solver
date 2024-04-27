#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 9

void printSudoku(int sudoku[SIZE][SIZE]);

void printSudoku(int sudoku[SIZE][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}

bool isValid(int sudoku[SIZE][SIZE], int row, int col, int num) {
    for(int i = 0; i < SIZE; i++) {
        if(sudoku[row][i] == num || sudoku[i][col] == num || sudoku[row - row % 3 + i / 3][col - col % 3 + i % 3] == num) {
            return false;
        }
    }
    return true;
}

bool solveSudoku(int sudoku[SIZE][SIZE]) {
    int row, col;

    bool found = false;
    for(row = 0; row < SIZE; row++) {
        for(col = 0; col < SIZE; col++) {
            if(sudoku[row][col] == 0) {
                found = true;
                break;
            }
        }
        if(found) break;
    }

    if(!found) return true;

    for(int num = 1; num <= SIZE; num++) {
        if(isValid(sudoku, row, col, num)) {
            sudoku[row][col] = num;

            if(solveSudoku(sudoku)) return true;

            sudoku[row][col] = 0;
        }
    }

    return false;
}

void generateSudoku(int sudoku[SIZE][SIZE]) {
    srand(time(NULL));

    // Fill the diagonal 3x3 grids
    for(int i = 0; i < SIZE; i += 3) {
        for(int j = 0; j < SIZE; j += 3) {
            int num = (i + j/3) % 9 + 1;
            for(int k = 0; k < 3; k++) {
                for(int l = 0; l < 3; l++) {
                    sudoku[i+k][j+l] = num;
                    num = (num % 9) + 1;
                }
            }
        }
    }

    // Shuffle rows and columns within 3x3 grids
    for(int i = 0; i < 3; i++) {
        int row1 = rand() % 3;
        int row2 = rand() % 3;
        int col1 = rand() % 3;
        int col2 = rand() % 3;

        // Swap rows
        for(int j = 0; j < SIZE; j++) {
            int temp = sudoku[i*3+row1][j];
            sudoku[i*3+row1][j] = sudoku[i*3+row2][j];
            sudoku[i*3+row2][j] = temp;
        }

        // Swap columns
        for(int j = 0; j < SIZE; j++) {
            int temp = sudoku[j][i*3+col1];
            sudoku[j][i*3+col1] = sudoku[j][i*3+col2];
            sudoku[j][i*3+col2] = temp;
        }
    }

    // Remove numbers randomly
    int numToKeep = 30; // Adjust this value to control difficulty
    while (numToKeep > 0) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (sudoku[row][col] != 0) {
            sudoku[row][col] = 0;
            numToKeep--;
        }
    }
}

int main() {
    int sudoku[SIZE][SIZE];

    generateSudoku(sudoku);

    printSudoku(sudoku);

    return 0;
}
