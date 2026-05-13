#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <stdio.h>

extern "C" {
#include "../matrix.h"
#include "../oddinacci.h"
#include "../mat0.h"
#include "../mat1.h"
#include "../mat2.h"
#include "../measure.h"
#include "../transpose.h"
}

#define ODDINACCI_ITERS 40


TEST_CASE("Oddinacci", "[Test]") {
    printf("Running Oddinacci test..\n");
    long val1 = 0;
    unsigned long slow = measure(oddinacci, ODDINACCI_ITERS, &val1);

    long val2 = 0;
    unsigned long fast = measure(oddinacci_fast, ODDINACCI_ITERS, &val2);

    printf("slow=%lu, fast=%lu\n", slow, fast);
    printf("factor=%f\n", (float) slow / fast);

    REQUIRE(val1 == val2);
    REQUIRE(slow / fast > 100);
    printf("Success!\n");
}

TEST_CASE("Matrix0", "[Mat0]") {
    printf("Running Mat0 test..\n");
    matrix_t mat;
    matrix_init(&mat, 10, 10, 0);

    printf("Running slow mat0...\n");
    long val1 = 0;
    unsigned long slow = measure_mat(mat0_slow, mat, &val1);

    printf("Running fast mat0...\n");
    long val2 = 0;
    unsigned long fast = measure_mat(mat0_fast, mat, &val2);

    float factor = (float) slow / fast;
    printf("slow=%lu, fast=%lu\n", slow, fast);
    printf("factor=%f\n", factor);

    REQUIRE(val1 == val2);
    REQUIRE(factor > 10);
    printf("Success!\n");
}

TEST_CASE("Matrix1", "[Mat1]") {
    printf("Running Mat1 test..\n");
    matrix_t mat;
    matrix_init(&mat, 10, 10, 1);

    long val1 = 0;
    unsigned long slow = measure_mat(mat1_slow, mat, &val1);

    long val2 = 0;
    unsigned long fast = measure_mat(mat1_fast, mat, &val2);

    printf("slow=%lu, fast=%lu\n", slow, fast);
    float factor = (float) slow / fast;
    printf("factor=%f\n", (float) slow / fast);

    REQUIRE(val1 == val2);
    REQUIRE(factor > 1.5);
    printf("Success!\n");
}

TEST_CASE("Matrix2", "[Mat2]") {
    printf("Running Mat2 test..\n");
    matrix_t mat;
    matrix_init(&mat, 4, 4, 2);

    printf("Calculating slow determinant: ");
    long val1 = 0;
    unsigned long slow = measure_mat(mat2_slow, mat, &val1);
    printf("\n");

    printf("Calculating fast determinant: ");
    long val2 = 0;
    unsigned long fast = measure_mat(mat2_fast, mat, &val2);
    printf("\n");

    float factor = (float) slow / fast;
    printf("slow=%lu, fast=%lu\n", slow, fast);
    printf("factor=%f\n", factor);

    REQUIRE(val1 == val2);
    REQUIRE(factor > 2.0);
    printf("Success!\n");
}


#define ROWS 10000
#define COLS 20000
#define TRANSPOSE_ITERS 10



TEST_CASE("Transpose", "[Transpose]") {
    printf("Running Transpose test..\n");

    printf("Creating matrices...\n");
    int* src = (int*) malloc(ROWS * COLS * sizeof(int));
    transpose_fill(src, ROWS, COLS);
    int* dst = (int*) malloc(ROWS * COLS * sizeof(int));
    memset(dst, 0, ROWS * COLS * sizeof(int));

    printf("Calculating slow transpose...\n");
    unsigned long slow = measure_transpose(transpose_slow, src, ROWS, COLS, dst, TRANSPOSE_ITERS);
    printf("Checking that slow transposition is correct...\n");
    REQUIRE(transpose_check(src, ROWS, COLS, dst));
    printf("transpose slow=%lu\n", slow);

    printf("Recreating matrices...\n");
    transpose_fill(src, ROWS, COLS);
    memset(dst, 0, ROWS * COLS * sizeof(int));

    printf("Calculating fast transpose...\n");
    unsigned long fast = measure_transpose(transpose_fast, src, ROWS, COLS, dst, TRANSPOSE_ITERS);
    printf("transpose fast=%lu\n", fast);
    printf("Checking that fast transposition is correct...\n");
    REQUIRE(transpose_check(src, ROWS, COLS, dst));
    float factor = (float) slow/fast;
    printf("factor=%f\n", factor);
    REQUIRE(factor >= 1.3);

    free(src);
    free(dst);
    printf("Success!\n");
}


#define TABLESIZE 1000
#define ITEMS 10000000
#define ITERS 15

// A random number generator to make sure everything is deterministic
static unsigned long next = 1;
/* RAND_MAX assumed to be 32767 */
static int myrand(void) {
    next = next * 1103515245 + 12345;
    return((unsigned)(next/65536) % 32768);
}
static void mysrand(unsigned seed) {
    next = seed;
}


// A structure to hold arguments to verify_table (see function below)
typedef struct arg {
    hashtable_t* hash;
    int items;
} arg_t;

/// Hash table loading uses random numbers for keys and values.
// Since srand is set to a seed of 0, we can repeat this deterministically.
// This function uses the same seed and the same sequence to get keys and values.
void verify_table(void* arg) {
    hashtable_t* hash = ((arg_t*) arg)->hash;
    int items =  ((arg_t*) arg)->items;

    // Hash table loading uses random numbers for keys and values.
    // Since srand is set to a seed of 0, we can repeat this deterministically.
    // printf("Loading hash table with keys and values...\n");
    mysrand(1);
    for (int i = 0; i < items; i++) {
        int key = myrand();
        int value = myrand();
        hashtable_add(hash, key, value);
        if (i % 1000000 == 0) {
            printf(".");
            fflush(stdout);
        }
    }
    // printf("Done\n");

    // Reset srand to same seed
    // printf("Verifying hash table(%p) with %d items...\n", hash, items);
    mysrand(1);
    int un = 0;
    for (int i = 0; i < items; i++) {
        int key = myrand();
        int expected = myrand();
        int value;
        bool rv = hashtable_lookup(hash, key, &value);
        assert(rv == true);
        // if (i % 1000000 == 0) {
        //     printf(".");
        //     fflush(stdout);
        // }
    }
    // printf("Success\n");
}

TEST_CASE("Hashtable", "[Hashtable]") {
    // Check that only smallmalloc is used
    printf("Checking that only smallmalloc is used... ");
    int rv = system("grep -E \"(\\Wmalloc)|(^malloc)\" list.c");
    REQUIRE(WEXITSTATUS(rv) != 0);
    printf("checks out ok\n");

    // Validating sizes - fast nodes should not be that big
    printf("Checking node sizes... ");
    assert(sizeof(fastnode_t) <= 256);
    printf("checks out ok.\n");

    // create a hash table and load it with values
    printf("Testing slow hash table...\n");
    hashtable_t* hash = hashtable_init(TABLESIZE, list_free, list_add, list_lookup);

    arg_t arg;
    arg.hash = hash;
    arg.items = ITEMS;
    unsigned long slow = measure_func(verify_table, &arg, ITERS);
    printf("Slow table took %lu\n", slow);
    hashtable_free(hash);

    printf("Testing fast hash table...\n");
    hashtable_t* fasthash = hashtable_init(
        TABLESIZE,
        (void (*)(node_t*)) fastlist_free,
        (void (*)(node_t**, int, int)) fastlist_add,
        (bool (*)(node_t*, int, int*)) fastlist_lookup);
    arg.hash = fasthash;
    arg.items = ITEMS;
    unsigned long fast = measure_func(verify_table, &arg, ITERS);
    printf("Fast table took %lu\n", fast);
    hashtable_free(fasthash);

    float factor = (float) slow / fast;
    printf("Speedup=%f\n", factor);
    assert(factor > 1.5);
}

/*
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
