#include <sys/time.h>
#include <stdio.h>
#include <assert.h>
#include "measure.h"

// Number of milliseconds
static unsigned long millis() {
    struct timeval tv;
    int rv = gettimeofday(&tv, NULL);
    assert(rv == 0);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// Return a non zero difference of either the diff or 1
static unsigned long nonzero_diff(long end, long start) {
    unsigned long d = end - start;
    if (d == 0) {
        return 1;
    } else {
        return d;
    }
}

unsigned long measure(long (*func)(long arg), long arg, long* result) {
    register unsigned long start = millis();
    *result = func(arg);
    register unsigned long end = millis();
    return nonzero_diff(end, start);
}

unsigned long measure_mat(long (*func)(matrix_t mat), matrix_t mat, long* result) {
    register unsigned long start = millis();
    *result = func(mat);
    register unsigned long end = millis();
    return nonzero_diff(end, start);
}

unsigned long measure_transpose(void (*func)(int*, int, int, int*), int* src, int rows, int cols, int* dst, int iters) {
    register unsigned long start = millis();
    for (int i = 0; i < iters; i++) {
        func(src, rows, cols, dst);
    }
    register unsigned long end = millis();
    return nonzero_diff(end, start);
}

// Measure how long the linked list function takes to execute
unsigned long measure_func(void (*func)(void*), void* arg, int iters) {
    register unsigned long start = millis();
    for (int i = 0; i < iters; i++) {
        func(arg);
    }
    register unsigned long end = millis();
    return nonzero_diff(end, start);
}
