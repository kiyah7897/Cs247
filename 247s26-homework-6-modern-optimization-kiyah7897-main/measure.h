#ifndef MEASURE_H
#define MEASURE_H

#include "matrix.h"
#include "hashtable.h"

// Measure how long the given function takes to execute
unsigned long measure(long (*func)(long), long arg, long* result);

// Measure how long the given function takes to execute
unsigned long measure_mat(long (*func)(matrix_t mat), matrix_t mat, long* result);

// Measure how long the transpose function takes to execute
unsigned long measure_transpose(void (*func)(int*, int, int, int*), int* src, int rows, int cols, int* dst, int iters);

// Measure how long the function takes to execute
unsigned long measure_func(void (*func)(void*), void* arg, int iters);

#endif // MEASURE_H
