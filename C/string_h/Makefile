CFLAGS = -Wall -Wextra -Werror -std=c11
LFLAGS = -lcheck -pthread -lcheck_pic -lrt -lm -lsubunit
CFILES = $(wildcard sources/*.c)
CFILES += $(wildcard sources/sprintf/*.c)
TEST_FILES = $(wildcard tests/*_test.c)

all: s21_string.a

s21_string.a:
	gcc -c $(CFLAGS) $(CFILES)
	ar rcs $@ *.o
	rm -f *.o

test: rebuild
	gcc $(CFLAGS) $(TEST_FILES) s21_string.a -o test.out $(LFLAGS)
	./test.out

gcov_report: CFLAGS += --coverage
gcov_report: test
	lcov -t "Report" -c -d ./ --output-file coverage.info
	genhtml coverage.info --output-directory report/
	rm -f *.out *.log *.gcno *.gcov *.gcda coverage.info

clang:
	clang-format -n *.h
	clang-format -n headers/*.h
	clang-format -n sources/*.c
	clang-format -n tests/*.c

clean:
	rm -rf *.o *.a *.out *.log *.gcno *.gcov *.gcda coverage.info report/

rebuild: clean s21_string.a