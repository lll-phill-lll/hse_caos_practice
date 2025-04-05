CC=gcc
CFLAGS=-Wall
CTESTFLAGS=$(CFLAGS) -fprofile-arcs -ftest-coverage

main: main.o averegator.o
	$(CC) $(CTESTFLAGS) $^ -o main

%.o: %.c
	$(CC) $(CTESTFLAGS) -c -MD $< -o $@

test_averegator: averegator.o test_averegator.o
	$(CC) $(CTESTFLAGS) $^ -o test_averegator

test: test_averegator
	./test_averegator

coverage: test_averegator
	./test_averegator
	gcov averegator.c

lcov: coverage
	mkdir lcov-report
	lcov --capture --directory . --output-file lcov-report/coverage.info
	genhtml lcov-report/coverage.info --output-directory lcov-report

clean:
	rm -f *.o *.d *.gcov *.gcno *.gcda main test_averegator a.out
	rm -rf lcov-report

-include *.d
