#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace std;
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#define ASSERT_EQ(a, b)     REQUIRE((a) == (b))
#define ASSERT_TRUE(a)      REQUIRE(a)
#define ASSERT_FALSE(a)     REQUIRE(!(a))

extern "C" {
#include "cache.h"
}

store_t store;
cache_t cache;

void LocalSetup(int store_size, int cache_size, policy_t policy) {
    // Create a store
    store_init(&store, store_size);

    // Initialize the pages to have a known pattern
    char val = 0;
    for (int i = 0; i < store_size; i++) {
        page_t* page = store_get(&store, i * PAGESIZE);
        for (int j = 0; j < PAGESIZE; j++) {
            page_set(page, j, (char) val++);
        }
    }

    // Create a cache
    cache_init(&cache, cache_size, &store, policy);
}

unsigned char ExpectedChar(int location) {
    return location;
}

TEST_CASE("Cache.Creating", "[Cache]") {
    LocalSetup(16, 4, FIFO);
}

TEST_CASE("Cache.FIFO", "[Cache]") {
    LocalSetup(16, 4, FIFO);

    int latency = 0;
    cache_get(&cache, 12, &latency);    // page 3
    ASSERT_EQ(STORE_LATENCY, latency);
    cache_get(&cache, 13, &latency);
    ASSERT_EQ(CACHE_LATENCY, latency);
    cache_get(&cache, 16, &latency);    // page 4
    cache_get(&cache, 22, &latency);    // page 5
    cache_get(&cache, 27, &latency);    // page 6

    ASSERT_TRUE(cache_contains(&cache, 3));
    ASSERT_TRUE(cache_contains(&cache, 4));
    ASSERT_TRUE(cache_contains(&cache, 5));
    ASSERT_TRUE(cache_contains(&cache, 6));
    ASSERT_FALSE(cache_contains(&cache, 1));

    unsigned char val = cache_get(&cache, 35, &latency);
    ASSERT_TRUE(cache_contains(&cache, 8));
    ASSERT_FALSE(cache_contains(&cache, 3));
    ASSERT_EQ(ExpectedChar(35), val);

    cache_get(&cache, 36, &latency);
    ASSERT_TRUE(cache_contains(&cache, 9));
    ASSERT_FALSE(cache_contains(&cache, 4));
}

TEST_CASE("Cache.RANDOM", "[Cache]") {
    LocalSetup(16, 4, FIFO);
}

TEST_CASE("Cache.LRU", "[Cache]") {
    LocalSetup(16, 4, LRU);

    int latency = 0;
    cache_get(&cache, 12, &latency);    // page 3
    ASSERT_EQ(STORE_LATENCY, latency);
    cache_get(&cache, 13, &latency);
    ASSERT_EQ(CACHE_LATENCY, latency);
    cache_get(&cache, 16, &latency);    // page 4
    cache_get(&cache, 22, &latency);    // page 5
    cache_get(&cache, 27, &latency);    // page 6

    ASSERT_TRUE(cache_contains(&cache, 3));
    ASSERT_TRUE(cache_contains(&cache, 4));
    ASSERT_TRUE(cache_contains(&cache, 5));
    ASSERT_TRUE(cache_contains(&cache, 6));
    ASSERT_FALSE(cache_contains(&cache, 1));

    unsigned char val = cache_get(&cache, 13, &latency);          // page 3
    ASSERT_EQ(ExpectedChar(13), val);

    cache_get(&cache, 35, &latency);          // page 8
    ASSERT_TRUE(cache_contains(&cache, 8));
    ASSERT_FALSE(cache_contains(&cache, 4));

    cache_get(&cache, 36, &latency);
    ASSERT_TRUE(cache_contains(&cache, 9));   // page 9
    ASSERT_FALSE(cache_contains(&cache, 5));
}

TEST_CASE("Cache.MRU", "[Cache]") {
    LocalSetup(16, 4, MRU);


    int latency = 0;
    cache_get(&cache, 12, &latency);    // page 3
    ASSERT_EQ(STORE_LATENCY, latency);
    cache_get(&cache, 13, &latency);
    ASSERT_EQ(CACHE_LATENCY, latency);
    cache_get(&cache, 16, &latency);    // page 4
    cache_get(&cache, 22, &latency);    // page 5
    unsigned char val = cache_get(&cache, 27, &latency);    // page 6
    ASSERT_EQ(ExpectedChar(27), val);

    ASSERT_TRUE(cache_contains(&cache, 3));
    ASSERT_TRUE(cache_contains(&cache, 4));
    ASSERT_TRUE(cache_contains(&cache, 5));
    ASSERT_TRUE(cache_contains(&cache, 6));
    ASSERT_FALSE(cache_contains(&cache, 1));

    cache_get(&cache, 23, &latency);          // page 5
    ASSERT_EQ(CACHE_LATENCY, latency);
    cache_get(&cache, 35, &latency);          // page 8
    ASSERT_EQ(STORE_LATENCY, latency);
    ASSERT_TRUE(cache_contains(&cache, 8));
    ASSERT_FALSE(cache_contains(&cache, 5));

    cache_get(&cache, 36, &latency);
    ASSERT_EQ(STORE_LATENCY, latency);
    ASSERT_TRUE(cache_contains(&cache, 9));   // page 9
    ASSERT_FALSE(cache_contains(&cache, 8));
}

TEST_CASE("Cache.Memory", "[Cache]") {
    printf("Testing leaks for ...\n");
#ifdef __APPLE__
const char* cmd2 =
    "echo \"1 2 3 4\" | leaks --atExit -- ./cache_sim";
#else
const char* cmd2 =
    "echo \"1 2 3 4\" | valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./cache_sim";
#endif
    int status2 = system(cmd2);
    REQUIRE(WEXITSTATUS(status2) == 0);
    printf("Success\n");
}

bool run_test(string cmd, string expected) {
    cmd += " > out";
    int status = system(cmd.c_str());
    REQUIRE(WEXITSTATUS(status) == 0);

    ifstream file("out");
    stringstream buffer;
    buffer << file.rdbuf(); // Read the file buffer into the stream
    string content = buffer.str(); // Convert stream to string

    cout << "Output was: " << endl;
    cout << content;
    file.close();

    cout << "Searching for " << expected << endl;
    REQUIRE(content.find(expected) != string::npos);
    return true;
}

string input = "0\n1\n2\n3\n9\n17\n20\n41\n10\n1\n40\n18";

TEST_CASE("Cache.FifoSim", "[Cache]") {
    string cmd = "echo \"" + input + "\" | " + "./cache_sim -p fifo < tests/test_input.txt";
    assert(run_test(cmd, "Total latency=66"));
}

TEST_CASE("Cache.LruSim", "[Cache]") {
    string cmd = "echo \"" + input + "\" | " + "./cache_sim -p lru < tests/test_input.txt";
    assert(run_test(cmd, "Total latency=75"));
}

TEST_CASE("Cache.MruSim", "[Cache]") {
    string cmd = "echo \"" + input + "\" | " + "./cache_sim -p mru < tests/test_input.txt";
    assert(run_test(cmd, "Total latency=57"));
}
