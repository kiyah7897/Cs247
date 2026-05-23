#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"


int main(int argc, char** argv) {
    // keep a counter of cache latency
    int total_latency = 0;
    int storesize = 16;
    int cachesize = 4;
    policy_t policy = FIFO;

    int opt;
    while((opt = getopt(argc, argv, "s:c:p")) != -1){
        switch(opt){
            case 's':
            storesize = atoi(optarg);

            break;
            case 'c':
            cachesize = atoi(optarg);

            break;

            case 'p':
            if(strcmp(optarg, "fifo") == 0){
                policy = FIFO;
            }else if(strcmp(optarg, "lru")== 0){
                policy = LRU;
            }else{
                policy = MRU;
            }
            break;

            default:
            printf("Usage: ./cache_sim [-s storesize] [-c cachesize] [-p policy]\n");
            break;
        }
    }

    store_t store;
    store_init(&store, storesize);

    cache_t cache;
    cache_init(&cache, cachesize, &store, policy);

    int location;
    int latency;
    while(scanf("%d", &location) == 1){
        cache_get(&cache, location, &latency);
        total_latency += latency;
    }
    store_free(&store);
    cache_free(&cache);
    // print out total latency at the end
    printf("Total latency=%d\n", total_latency);

    // Make sure to exit cleanly when you fix this code
    return 0;
}
