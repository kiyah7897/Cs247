#include <stdlib.h>
#include "store.h"

// Initialize a memory store with the given number of pages
void store_init(store_t* store, int numpages) {
    store->pages = malloc(numpages * sizeof(page_t));
    memset(store->pages , 0, numpages * sizeof(page_t));
    store->numpages = numpages;
}

// Free memory allocated for the store
void store_free(store_t* store) {
    free(store->pages);
}

// Return the page corresponding to the given memory location
page_t* store_get(store_t* store, int location) {
    int pageNumber = location/PAGESIZE;
    return &store->pages[pageNumber];
}
