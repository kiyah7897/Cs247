CC=gcc
CFLAGS=-I. -g
CPPFLAGS=-I. -g -std=c++11
DEPS =
OBJ = page.o store.o cache.o main.o
TARGET=cache_sim
TESTTARGET=cache_test

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CPPFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS)

clean:
	rm -f *.o *.out tests/*.o
	-docker image rm seemongtan/build:latest

run: default
	./$(TARGET)

$(TESTTARGET): $(OBJ) tests/test_main.o
	g++ page.o store.o cache.o tests/test_main.o -o $(TESTTARGET)

test-create: $(TESTTARGET)
	./cache_test Cache.Creating

test-fifo: $(TESTTARGET)
	./cache_test Cache.FIFO

test-lru: $(TESTTARGET)
	./cache_test Cache.LRU

test-mru: $(TESTTARGET)
	./cache_test Cache.MRU

test-memory: $(TESTTARGET) $(TARGET)
	./cache_test Cache.Memory

test-sim-fifo: $(TESTTARGET) $(TARGET)
	./cache_test Cache.FifoSim

test-sim-lru: $(TESTTARGET) $(TARGET)
	./cache_test Cache.LruSim

test-sim-mru: $(TESTTARGET) $(TARGET)
	./cache_test Cache.MruSim

test-style:
	cpplint *.c *.h

test: $(TESTTARGET) $(TARGET)
	./cache_test

run-on-docker:
	docker run -it --rm --mount type=bind,src=.,dst=/app seemongtan/build:latest
