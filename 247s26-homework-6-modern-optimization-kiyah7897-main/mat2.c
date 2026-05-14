#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "matrix.h"
#include "measure.h"

long determinant(matrix_t mat) {
    // These output statements help see progress in the 
    // calculation
    puts(".");
    fflush(stdout);

    assert(matrix_rows(mat) == matrix_cols(mat));
    if (matrix_rows(mat) == 1) {
        return matrix_get(mat, 0, 0);
    }

    long sum = 0;
    for (int i = 0; i < matrix_cols(mat); i++) {
        matrix_t submat;
        matrix_submatrix(mat, i, &submat);
        long subvalue = matrix_get(mat, 0, i) * determinant(submat);
        if (i % 2 == 0) {
            sum += subvalue;
        } else {
            sum -= subvalue;
        }
        matrix_free(submat);
    }
    return sum;
}

long mat2_slow(matrix_t mat) {
    return determinant(mat);           // calculate the determinant
}

long helper(matrix_t mat, int row, int* current, int size);


long fast_determinant(matrix_t mat) {
    // These output statements help see progress in the
    // calculation
    puts("-");
    fflush(stdout);

    int n = matrix_cols(mat);
    int current[n];
    for(int i = 0; i < n; i++){
        current[i] = i;
    }
   return helper(mat, 0 ,current, n);
}
long helper(matrix_t mat, int row, int* current, int size){
    if(size == 1){
        return matrix_get(mat,row, current[0]);
    }
    long sum = 0;
    for (int i = 0; i < size; i ++){
        long element = matrix_get(mat, row, current[i]);
    
    int new_arr[size - 1];

    int count = 0;
    for(int j = 0; j < size; j++){
        if(j != i){
            new_arr[count++] = current[j];
        }
    }
    long result= helper(mat,row + 1, new_arr, size -1) * element;
    if (i % 2 == 0) {
    sum += result;
    }else {
    sum -= result;
    }
}
    return sum;
}


long mat2_fast(matrix_t mat) {
    return fast_determinant(mat);
}
