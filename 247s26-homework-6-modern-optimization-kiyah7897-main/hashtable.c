#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"




// Initialize a hash table of the given size
hashtable_t* hashtable_init(
    int size,
    void (*listfreefunc)(node_t*),
    void (*listaddfunc)(node_t**, int, int),
    bool (*listlookupfunc)(node_t*, int, int*)
) {
    hashtable_t* hash = (hashtable_t*) malloc(sizeof(hashtable_t));
    hash->size = size;
    hash->listadd = listaddfunc;
    hash->listfree = listfreefunc;
    hash->listlookup = listlookupfunc;
    hash->data = (node_t**) calloc(size, sizeof(node_t*));
    return hash;
}

// Free a hash table
void hashtable_free(hashtable_t* hash) {
    for (int i = 0; i < hash->size; i++) {
        hash->listfree(hash->data[i]);
    }
    free(hash->data);
    free(hash);
}

// Add key value mapping to the hash table
void hashtable_add(hashtable_t* hash, int key, int value) {
    int index = key % hash->size;
    hash->listadd(&hash->data[index], key, value);
#ifdef DEBUG
    int actual = 0;
    bool rv = hash->listlookup(hash->data[index], key, &actual);
    assert(rv == true);
    assert(actual == value);
#endif
}

// Lookup key in hash table. Return true on success or false on failure.
// Set *pvalue to the value if found.
bool hashtable_lookup(hashtable_t* hash, int key, int* pvalue) {
    int index = key % hash->size;
    return hash->listlookup(hash->data[index], key, pvalue);
}
