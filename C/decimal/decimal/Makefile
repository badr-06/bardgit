CFLAGS = -Wall -Wextra -Werror -std=c11
LFLAGS = -lcheck -pthread -lcheck_pic -lrt -lm -lsubunit
CFILES = $(wildcard sources/*.c)
TEST_FILES = $(wildcard tests/*_test.c)

all: s21_decimal.a

s21_decimal.a:
	gcc -c $(CFLAGS) $(CFILES)
	ar rcs $@ *.o
	rm -f *.o

test: rebuild
	gcc $(CFLAGS) $(TEST_FILES) s21_decimal.a -o test.out $(LFLAGS)
	./test.out

gcov_report: CFLAGS += --coverage
gcov_report: test
	lcov -t "Report" -c -d ./ --output-file coverage.info
	genhtml coverage.info --output-directory report/
	rm -f *.out *.log *.gcno *.gcov *.gcda coverage.info

clean:
	rm -rf *.o *.a *.out *.log *.gcno *.gcov *.gcda .clang-format coverage.info report/

rebuild: clean s21_decimal.a

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n s21_decimal.h
	clang-format -n */*.h
	clang-format -n */*.c

clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -i s21_decimal.h
	clang-format -i */*.h
	clang-format -i */*.c
