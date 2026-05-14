#include <stdio.h>
#include <time.h>
#include "matrix.h"
#include "measure.h"

long mat1_slow(matrix_t mat) {
    long sum = 0;
    for (int i = 0; i < matrix_rows(mat); i++) {
        int row_result = 0;
        for (int j = 0; j < matrix_cols(mat); j++) {
            row_result += matrix_get(mat, i, 0) + matrix_get(mat, i, j);
        }
        printf("%d %d\n", i, row_result);
        sum += row_result;
    }
    return sum;
}

long mat1_fast(matrix_t mat) {
    long sum = 0;
    int row = matrix_rows(mat);
    int cols = matrix_cols(mat);
    for (int i = 0; i < row; i ++){
        int row_result = 0;
        int orgi = matrix_get(mat ,i ,0);
        for (int j = 0; j <cols; j++){
            row_result += orgi + matrix_get(mat, i ,j);
        }
        sum += row_result;
    }
    return sum;
}
