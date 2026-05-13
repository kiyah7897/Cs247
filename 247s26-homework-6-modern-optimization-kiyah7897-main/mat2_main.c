#include <stdio.h>
#include <assert.h>
#include "matrix.h"
#include "mat2.h"
#include "measure.h"

int main() {
    matrix_t mat;
    matrix_init(&mat, 4, 4, 2);

    long val1 = 0;
    unsigned long slow = measure_mat(mat2_slow, mat, &val1);
    printf("mat1 det=%ld\n",  val1);

    matrix_init(&mat, 4, 4, 2);
    long val2 = 0;
    unsigned long fast = measure_mat(mat2_fast, mat, &val2);
    printf("mat2 det=%ld\n",  val2);

    assert(val1 == val2);

    printf("slow=%lu, fast=%lu\n", slow, fast);
    printf("Speedup=%f\n", (float) slow / fast);
}
