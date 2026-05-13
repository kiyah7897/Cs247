#include <stdlib.h>
#include "oddinacci.h"
#include <stdio.h>

long oddinacci(long n) {
    if (n == 0 || n == 1) {
        return n;
    } else if (n % 2 == 0) {
        return oddinacci(n - 1) + oddinacci(n - 2);
    } else {
        return oddinacci(n - 1) + oddinacci(n - 2) + oddinacci(n - 3);
    }
}

long oddinacci_fast(long n) {
    long* array = malloc((n + 1) * sizeof(long));
    if(n == 0){
        free(array);
        return 0;
    }
    if(n == 1){
        free(array);
        return 1;
    }
    for(int i = 2; i <= n; i++){
        if(i % 2 && i >= 3){
            array[i] = array[i - 1] + array[i - 2]+ array[i - 3];
        }else{
            array[i] = array[i - 1] + array[i - 2];
        }
    }
    long result = array[n];
    free(array);
    return result;
}
