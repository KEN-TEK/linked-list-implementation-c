CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -g

all: demo tests

demo: main.c linked_list.c linked_list.h
	$(CC) $(CFLAGS) -o demo main.c linked_list.c

tests: tests.c linked_list.c linked_list.h
	$(CC) $(CFLAGS) -o tests tests.c linked_list.c

test: tests
	./tests

run: demo
	./demo

clean:
	rm -f demo tests

.PHONY: all test run clean
