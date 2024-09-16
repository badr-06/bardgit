CFLAGS = -Wall -Wextra -Werror -std=c11
LFLAGS = -lcheck -pthread -lcheck_pic -lrt -lm -lsubunit
CFILES = $(wildcard sources/*.c)
TEST_FILES = $(wildcard tests/unit_tests.c)


all: s21_matrix.a

s21_matrix.a:
	gcc -c $(CFLAGS) $(CFILES)
	ar rcs $@ *.o
	rm -f *.o


test: rebuild
	gcc $(CFLAGS) $(TEST_FILES) s21_matrix.a -o test.out $(LFLAGS)
	./test.out > test.txt

gcov_report: CFLAGS += --coverage
gcov_report: test
	lcov -t "Report" -c -d ./ --output-file coverage.info
	genhtml coverage.info --output-directory report/
	rm -f *.out *.log *.gcno *.gcov *.gcda coverage.info

clean:
	rm -rf *.txt *.o *.a *.out *.log *.gcno *.gcov *.gcda .clang-format coverage.info report/

rebuild: clean s21_matrix.a

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n sources/*.c
	clang-format -n s21_matrix.h
	clang-format -n tests/*.c

clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -i sources/*.c
	clang-format -i s21_matrix.h
	clang-format -i tests/*.c

valgrind:
	valgrind --leak-check=full --track-origins=yes -s ./test.out 