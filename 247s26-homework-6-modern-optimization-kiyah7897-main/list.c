#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "smallmalloc.h"


// Free the list and all associated nodes
void list_free(node_t* list) {
    // Free all nodes
    for(node_t* node = list; node != NULL; ) {
        node_t* nextnode = node->next;
        free(node);
        node = nextnode;
    }
}

// Add the value to the end of the list if it's not already in the list.
// If already in the list, update the value to the new one.
void list_add(node_t** list, int key, int value) {
    node_t** nodep = list;
    for (; *nodep != NULL; nodep = &(*nodep)->next) {
        if ((*nodep)->key == key) {
            (*nodep)->value = value;
            return;
        }
    }
    node_t* newnode = (node_t*) smallmalloc(sizeof(node_t));
    newnode->key = key;
    newnode->value = value;
    newnode->next = NULL;
    *nodep = newnode;
}


// Lookup the key in the list. Return true on success or false on failure.
// The value is set in *pvalue.
bool list_lookup(node_t* list, int key, int* pvalue) {
    for (node_t* node = list; node != NULL; node = node->next) {
        if (key == node->key) {
            *pvalue = node->value;
            return true;
        }
    }
    return false;
}


// --------------------------


// Free the list and all associated nodes
void fastlist_free(fastnode_t* fastlist) {
    // Your code here
    fastnode_t* node = fastlist;
    while(node != NULL){
        fastnode_t* next = node->next;
        free(node);
        node = next;
    }
}

// Add the value to the end of the list
void fastlist_add(fastnode_t** fastlist, int key, int value) {
    // Your code here
    if (*fastlist == NULL){
        fastnode_t* newNode = smallmalloc(sizeof(fastnode_t));
        newNode->data[0].key = key;
        newNode->data[0].value = value;
        newNode->top = 1;
        newNode->next = NULL;
        *fastlist = newNode;
        return;
    }
    fastnode_t* node = *fastlist;
    while(node != NULL){
        for (int i = 0; i < node->top; i++){
            if (node->data[i].key == key){
            node->data[i].value = value;
            return;
        }
        if (node->top < SIZE){
            node->data[node->top].key = key;
            node->data[node->top].value = value;
            node->top++;
            return;
        }
        if(node->top == SIZE && node->next == NULL){
            fastnode_t* newNode = smallmalloc(sizeof(fastnode_t));
            newNode->data[0].key = key;
            newNode->data[0].value = value;
            newNode->top = 1;
            newNode->next = NULL;
            node->next = newNode;
            return;
        }
            node = node->next;
        
    }
    }
    return;

}

// Lookup the key in the list and set *pvalue to it if found.
// Return true on success or false on failure.
bool fastlist_lookup(fastnode_t* fastlist, int key, int* pvalue) {
    // Your code here
    fastnode_t* node = fastlist;
    while(node != NULL){
        for (int i = 0; i < node->top; i++){
            if(node->data[i].key == key){
                *pvalue = node->data[i].value;
                return true;
            }
        }
            node = node->next;
    }
    return false;
}
