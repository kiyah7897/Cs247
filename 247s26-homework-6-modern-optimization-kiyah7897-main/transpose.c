#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "transpose.h"


// Fill a matrix of ints of rows and cols with random values
void transpose_fill(int* matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = rand() % 100;
        }
    }
}

// Check that the src and dst matrices are transposes of each other
bool transpose_check(int* src, int rows, int cols, int* dst) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (src[i * cols + j] != dst[j * rows + i]) {
                return false;
            }
        }
    }
    return true;
}

// Print the matrix -- useful for debugging
void print_mat(char* title, int* mat, int rows, int cols) {
    printf("%s: [\n", title);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", mat[i * cols + j]);
        }
        printf("\n");
    }
    printf("]\n");
}

// Slow transpose using dst[j][i] = src[i][j]
void transpose_slow(int* src, int rows, int cols, int* dst) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dst[j * rows + i] = src[i * cols + j];
        }
    }
}


void transpose_fast(int* src, int rows, int cols, int* dst) {
    // Your code here
}
