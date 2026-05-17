#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"
#include "measure.h"


#define TABLESIZE 1000
#define ITEMS 10000000

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

// Hash table loading uses random numbers for keys and values.
// Since srand is set to a seed of 0, we can repeat this deterministically.
// This function uses the same seed and the same sequence to get keys and values.
void verify_table(void* arg) {
    hashtable_t* hash = ((arg_t*) arg)->hash;
    int items =  ((arg_t*) arg)->items;

    // Hash table loading uses random numbers for keys and values.
    // Since srand is set to a seed of 0, we can repeat this deterministically.
    printf("Loading hash table with keys and values...\n");
    mysrand(1);
    for (int i = 0; i < items; i++) {
        int key = myrand();
        int value = myrand();
        hashtable_add(hash, key, value);
        if (i % 10000 == 0) {
            printf(".");
            fflush(stdout);
        }
    }
    printf("Done\n");

    // Reset srand to same seed
    printf("Verifying hash table(%p) with %d items...\n", hash, items);
    mysrand(1);
    int un = 0;
    for (int i = 0; i < items; i++) {
        int key = myrand();
        int expected = myrand();
        int value;
        bool rv = hashtable_lookup(hash, key, &value);
        assert(rv == true);
        if (i % 10000 == 0) {
            printf(".");
            fflush(stdout);
        }
    }
    printf("Success\n");
}

void testlist() {
    node_t* list = NULL;

#define MAXTEST 100000
    for (int i = 0; i < MAXTEST; i++) {
        list_add(&list, i, 2*i);
    }
    for (int i = 0; i < MAXTEST; i++) {
        int value;
        assert(list_lookup(list, i, &value) == true);
        assert(value == 2 * i);
    }
    printf("ok\n");
}



int main() {
    // create a hash table and load it with values
    printf("Creating slow hash table...\n");
    hashtable_t* hash = hashtable_init(TABLESIZE, list_free, list_add, list_lookup);
    arg_t arg;
    arg.hash = hash;
    arg.items = ITEMS;
    double slow = measure_func(verify_table, &arg,1);
    printf("Slow table took %f\n", slow);
    hashtable_free(hash);

    printf("Creating fast hash table...\n");
    hashtable_t* fasthash = hashtable_init(
        TABLESIZE,
        (void (*)(node_t*)) fastlist_free,
        (void (*)(node_t**, int, int)) fastlist_add,
        (bool (*)(node_t*, int, int*)) fastlist_lookup);
    arg.hash = fasthash;
    arg.items = ITEMS;
    double fast = measure_func(verify_table, &arg,1);
    printf("Fast table took %f\n", fast);
    hashtable_free(fasthash);

    printf("Speedup=%f\n", slow / fast);

    return 0;
}
