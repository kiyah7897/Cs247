#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#include <stdbool.h>

// Fill a matrix of ints of rows and cols with random values
void transpose_fill(int* mat, int rows, int cols);

// Check that the src and dst matrices are transposes of each other
bool transpose_check(int* src, int rows, int cols, int* dst);

// Slow transpose using dst[j][i] = src[i][j]
void transpose_slow(int* src, int rows, int cols, int* dst);

// Fast transposition
void transpose_fast(int* src, int rows, int cols, int* dst);

// Print the matrix -- useful for debugging
void print_mat(char* title, int* mat, int rows, int cols);

#endif // TRANSPOSE_H
