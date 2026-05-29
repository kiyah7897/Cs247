# This is how you write comments
# Use gcc as a compiler
CC=gcc
CPP=g++
CFLAGS=-I. -g
CPPFLAGS=-I. -g -std=c++11
DEPS =
OBJ = elfloader.o
TARGET = elfloader
TESTTARGET = test_elfloader
TESTOBJ = tests/test_main.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(DEPS)
		$(CPP) -c -o $@ $< $(CPPFLAGS)

default: $(TARGET)

$(TARGET): $(OBJ)
		$(CPP) -o $@ $^ $(CFLAGS)

$(TESTTARGET): $(TESTOBJ) $(TARGET)
		$(CPP) -o $@ $(TESTOBJ) $(CPPFLAGS)

tests/test1: tests/test1.o
	ld -N -e main -Ttext 0 -o $@ tests/test1.o

tests/test1.o: tests/test1.c
	$(CC) -c -fno-pic -static -fno-builtin -ggdb -fno-omit-frame-pointer $^ -o $@

tests/test2: tests/test2.o
	ld -N -e main -Ttext 0 -o $@ $^

tests/test2.o: tests/test2.c
	$(CC) -c -fno-pic -static -fno-builtin -ggdb -fno-omit-frame-pointer $^ -o $@

tests/test3: tests/test3.o
	ld -N -e main -o $@ $^

tests/test3.o: tests/test3.c
	$(CC) -c -fno-pic -static -fno-builtin -ggdb -fno-omit-frame-pointer tests/test3.c -o tests/test3.o

tests/test4: tests/test3.c
	$(CC) -c $^ -o $@

test-test1: $(TESTTARGET) $(TARGET)
	./$(TESTTARGET) Elf.test1

test-test2: $(TESTTARGET) $(TARGET)
	./$(TESTTARGET) Elf.test2

test-test3: $(TESTTARGET) $(TARGET)
	./$(TESTTARGET) Elf.test3

test-malformed: $(TESTTARGET) $(TARGET) tests/test4
	./$(TESTTARGET) Elf.malformed

test-nofile: $(TESTTARGET) $(TARGET)
	./$(TESTTARGET) Elf.nofile

test-style:
	cpplint elfloader.c

test: test-test1 test-test2 test-test3 test-malformed test-nofile

clean:
	rm -f *.o $(TARGET) $(TESTTARGET) tests/*.o tests/test1 tests/test2 tests/test3 tests/test4 out

clean-docker:
	-docker image rm seemongtan/build:latest

run-on-docker:
	docker run -it --rm --mount type=bind,src=.,dst=/app --platform linux/amd64 seemongtan/build:latest
