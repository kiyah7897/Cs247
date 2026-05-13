#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

// The node holds a linked list of key/value pairs
typedef struct node {
    int key;
    int value;
    struct node* next;
} node_t;

// Free the list and all associated nodes
void list_free(node_t* list);

// Add the value to the end of the list if it's not already in the list.
// If already in the list, update the value to the new one.
void list_add(node_t** list, int key, int value);

// Lookup the key in the list. Return true on success or false on failure.
// The value is set in *pvalue.
bool list_lookup(node_t* list, int key, int* pvalue);


// -----------------------------------
// A fast linked list. This is the equivalent of the linked list above and is
// intended to be used as a drop in replacement for linkedlist_t in hashtable_t

// A fast node uses an array of values to stay within
typedef struct fastnode {
    int top;
    int bottom;
#define SIZE 30
    struct {
        int key;
        int value;
    } data[SIZE];
    struct fastnode* next;
} fastnode_t;



// Free the fast list and all associated nodes
void fastlist_free(fastnode_t* fastlist);

// Add the value to the end of the list if it's not already in the list.
// If already in the list, update the value to the new one.
void fastlist_add(fastnode_t** fastlist, int key, int value);

// Lookup key in the list and set *pvalue to the associated value if found.
// Return true on success or false on failure.
bool fastlist_lookup(fastnode_t* fastlist, int key, int* pvalue);

#endif // LINKEDLIST_H
