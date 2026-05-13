#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transpose.h"
#include "measure.h"

#define ROWS 20000
#define COLS 10000

int src[ROWS * COLS * sizeof(int)];
int dst[ROWS * COLS * sizeof(int)];


int main(int argc, char** argv) {
    printf("Creating matrices...\n");
    int* src = (int*) malloc(ROWS * COLS * sizeof(int));
    transpose_fill(src, ROWS, COLS);
    int* dst = (int*) malloc(ROWS * COLS * sizeof(int));
    memset(dst, 0, ROWS * COLS * sizeof(int));

    printf("Calculating slow transpose...\n");
    double slow = measure_transpose(transpose_slow, src, ROWS, COLS, dst);
    printf("Checking that slow transposition is correct...\n");
    if (!transpose_check(src, ROWS, COLS, dst)) {
        printf("Failed transpose check\n");
        return 1;
    }
    printf("transpose slow=%f\n", slow);

    printf("Recreating matrices...\n");
    transpose_fill(src, ROWS, COLS);
    memset(dst, 0, ROWS * COLS * sizeof(int));

    printf("Calculating fast transpose...\n");
    double fast = measure_transpose(transpose_fast, src, ROWS, COLS, dst);
    printf("transpose fast=%f\n", fast);
    printf("Checking that fast transposition is correct...\n");
    if (!transpose_check(src, ROWS, COLS, dst)) {
        printf("Failed transpose check\n");
        return 1;
    }

    double factor = slow/fast;
    printf("factor=%f\n", factor);

    free(src);
    free(dst);
}
