#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "cache.h"


void cache_init(cache_t* cache, int size, store_t* store, policy_t policy) {
    cache->store = store;
    cache->policy = policy;
    cache->size = size;
    chche->entries = malloc(size * sizeof(entry_t));
    cache->counter = 0;
    cache->numEntries = 0;
}

void cache_free(cache_t* cache) {
    free(cache->entries);
}

unsigned char cache_get(cache_t* cache, int memory_location, int* latency) {
    // Return the value in memory corresponding to the given memory location.
    // This function looks up whether the page exists in the cache first.
    int pageNumber = memory_location / PAGESIZE;
    if (cache_contains(cache , pageNumber)){
        for (int i = 0; i < cache->size; i++){
            if(cache->entries[i].page == NULL){
                continue
            }
            if(cache->entries[i].page->pageno == pageNumber){
                *latency = CACHE_LATENCY;
                cache->entries[i].timeStamp = cache->counter;
                cache->counter++;
                return cache->entries[i].page->bytes[memory_location % PAGESIZE];
            }
        }
            page_t* current = store_get(cache->store, memory_location);
            if(cache->numEntries != cache->size){
                cache->entries[cache->numEntries].page = current;
                *latency = STORE_LATENCY;
                cache->entries[cache->numEntries].timeStamp = cache->counter;
                cache->numEntries++;
                cache->counter++;
                return current->bytes[memory_location % PAGESIZE];
            }else{
                *latency = STORE_LATENCY;
                switch(cache->policy){
                    case FIFO:
                    //find entry with lowest timeStamp insert first
                    int lastUsed = cache->entries[0].timeStamp;
                    int index = 0;
                    for (int i = 0; i < cache->size; i++){
                        if(cache->entries[i].timeStamp < lastUsed){
                            lastUsed = cache->entries[i].timeStamp;
                            index = i;
                        }

                    }
                            cache->entries[index].page = current;
                            cache->entries[index].timeStamp = cache->counter;
                            cache->counter++;
                    
                    break;

                    case LRU:
                    int lastUsed = cache->entries[0].timeStamp;
                    int index = 0;
                    for (int i = 0; i < cache->size; i++){
                        if(cache->entries[i].timeStamp < lastUsed){
                            lastUsed = cache->entries[i].timeStamp;
                            index = i;
                        }
                    }
                        cache->entries[index].page = current;
                        cache->entries[index].timeStamp = cache->counter;
                        cache->counter++;

                    break;

                    case MRU:
                    int lastUsed = cache->entries[0].timeStamp;
                    int index = 0;
                    for (int i = 0; i < cache->size; i++){
                        if(cache->entries[i].timeStamp > lastUsed){
                            lastUsed = cache->entries[i].timeStamp;
                            index = i;
                        }
                    }
                        cache->entries[index].page = current;
                        cache->entries[index].timeStamp = cache->counter;
                        cache->counter++;

                    break;
                }
            }
            return current->bytes[memory_location % PAGESIZE];
    }
    return 0;
}

bool cache_contains(cache_t* cache, int page_no) {
    for(int i = 0; i < cache->size; i ++){
        if(cache->entries[i].page == NULL){
            continue;
        }
        if(cache->entries[i].page->pageno == page_no){
            return true;
        }
    }
    return false;
}
