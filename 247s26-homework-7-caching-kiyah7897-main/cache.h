#ifndef CACHE_H_
#define CACHE_H_

#include <stdbool.h>
#include "page.h"
#include "store.h"

#define CACHE_LATENCY 1

// A cache entry is a pointer to a page, and some metadata associated with it
typedef struct {
    page_t* page;
    int timeStamp;
} entry_t;

// Cache replacement policies
typedef enum {
    FIFO,
    RANDOM,
    LRU,
    MRU,
} policy_t;

// A cache is simply an array of cache entries of the given size
typedef struct cache {
    store_t* store;

    policy_t policy;
    int size;
    entry_t* entries;

    int counter;
    int numEntries;
} cache_t;



// Initialize a cache of the given size number of pages.
// The cache is backed by the store and is governed with the given cache
// replacement policy.
void cache_init(cache_t* cache, int size, store_t* store, policy_t policy);

// Free the memory allocated for the cache
void cache_free(cache_t* cache);

// Return the value in memory corresponding to the given memory location.
// This function looks up whether the page exists in the cache first.
// If it does, it retrieves the Page from the cache, and updates the cache,
// and returns the value.
// If the Page is not present, it goes to the store to retrieve the page,
// updates the cache and returns the value.
// The time required for the get is set in the pointer latency.
unsigned char cache_get(cache_t* cache, int memory_location, int* latency);

// Return true if the page with page_no is present in the cache
bool cache_contains(cache_t* cache, int page_no);

#endif   // CACHE_H_
