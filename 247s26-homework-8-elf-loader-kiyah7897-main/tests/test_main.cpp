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

int run_test(string cmd, string expected) {
    cmd += " > out";
    int status = system(cmd.c_str());
    int rv = WEXITSTATUS(status);
    if (rv != 0) {
        return rv;
    }

    ifstream file("out");
    stringstream buffer;
    buffer << file.rdbuf(); // Read the file buffer into the stream
    string content = buffer.str(); // Convert stream to string

    cout << "Output was: " << endl;
    cout << content;
    file.close();

    cout << "Searching for " << expected << "..." << endl;
    REQUIRE(content == expected);
    cout << "Test passed!" << endl;
    return 0;
}

TEST_CASE("Elf.test1", "[Elf]") {
    string cmd = "./elfloader tests/test1 3 4";
    run_test(cmd, "Answer=7\n");
}

TEST_CASE("Elf.test2", "[Elf]") {
    string cmd = "./elfloader tests/test2 10 13";
    run_test(cmd, "Answer=32\n");
}

TEST_CASE("Elf.test3", "[Elf]") {
    string cmd = "./elfloader tests/test3 22 19";
    run_test(cmd, "Answer=16\n");
}

TEST_CASE("Elf.malformed", "[Elf]") {
    // ELF header is malformed
    cout << "Expecting a return value of 3" << endl;
    string cmd = "./elfloader tests/test4 5 6";
    REQUIRE(run_test(cmd, "") == 3);
    cout << "Test passed!" << endl;


    // Program header is malformed
    cout << "Expecting a return value of 3" << endl;
    string cmd2 = "./elfloader tests/test5-prebuilt 5 6";
    REQUIRE(run_test(cmd2, "") == 3);
    cout << "Test passed!" << endl;

    // Elf header is bad
    cout << "Expecting a return value of 2" << endl;
    string cmd3 = "./elfloader tests/test6-prebuilt 5 6";
    REQUIRE(run_test(cmd3, "") == 2);
    cout << "Test passed!" << endl;
}

TEST_CASE("Elf.nofile", "[Elf]") {
    // non existent test file
    cout << "Expecting a return value of 2" << endl;
    string cmd = "./elfloader nonexistent 55 66";
    // expected exit code 2 (file not found)
    REQUIRE(run_test(cmd, "") == 2);
    cout << "Test passed!" << endl;

    // wrong args
    // cout << "Expecting a return value of 1" << endl;
    string cmd2 = "./elfloader tests/test1 55 66 77";
    // expected exit code 1 (wrong args))
    REQUIRE(run_test(cmd2, "") == 1);
    cout << "Test passed!" << endl;

    // wrong args
    cout << "Expecting a return value of 1" << endl;
    string cmd3 = "./elfloader ";
    // expected exit code 1 (wrong args))
    REQUIRE(run_test(cmd3, "") == 1);
    cout << "Test passed!" << endl;
}
