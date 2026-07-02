#!/bin/bash
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MODEL = model/*.c
CONTROLLER = controller/*.c
CLI = cli/*.c


all: install tests

install: build
	$(CC) $(CFLAGS) main.c $(MODEL) $(CONTROLLER) $(CLI) -lncurses -o build/consol

uninstall:
	rm -f build/consol

tests: build
	gcc tests/test.c model/*.c -lcheck -lsubunit -lm -o build/test

valgrind: tests
	valgrind -s --leak-check=full ./build/test

clang:
	clang-format -n model/*.c controller/*.c cli/*.c model/*.h controller/*.h cli/*.h tests/test.c
	clang-format -i model/*.c controller/*.c cli/*.c model/*.h controller/*.h cli/*.h tests/test.c

build:
	mkdir -p build

clean:
	rm -rf build/test build/consol