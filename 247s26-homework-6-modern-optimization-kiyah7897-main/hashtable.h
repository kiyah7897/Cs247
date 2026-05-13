#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include "list.h"

// A hash table
typedef struct {
    int size;                               // size of the table
    node_t** data;                          // the array of lists itself
    void (*listfree)(node_t*);              // the function used to free a list
    void (*listadd)(node_t**, int, int);     // the function used to add data to a list
    bool (*listlookup)(node_t*, int, int*); // the function to lookup keys in a list
} hashtable_t;

// Initialize a hash table of the given size.
// The hash table can operate on multiple kinds of lists, and needs to know
// what the functions to create, add and free lists are.
hashtable_t* hashtable_init(
    int size,
    void (*listfreefunc)(node_t*),
    void (*listaddfunc)(node_t**, int, int),
    bool (*listlookupfunc)(node_t*, int, int*)
);

// Free a hash table
void hashtable_free(hashtable_t* hash);

// Add key value mapping to the hash table
void hashtable_add(hashtable_t* hash, int key, int value);

// Lookup key in hash table. Return true on success or false on failure.
// Set *pvalue to the value if found.
bool hashtable_lookup(hashtable_t* hash, int key, int* pvalue);

#endif // HASHTABLE_H
