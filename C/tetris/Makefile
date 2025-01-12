CFLAGS = -Wall -Wextra -Werror -std=c11
LFLAGS = -lcheck -pthread -lcheck_pic -lrt -lm -lsubunit -lncurses
CFILES = $(wildcard backend.c)
TEST_FILES = $(wildcard test.c)


all: s21_tetris.a

s21_tetris.a:
	gcc -c $(CFLAGS) $(CFILES)
	ar rcs $@ *.o
	rm -f *.o


test:
	gcc $(CFLAGS) $(TEST_FILES) s21_tetris.a -o test.out $(LFLAGS)

gcov_report: CFLAGS += --coverage
gcov_report: test
	lcov -t "Report" -c -d ./ --output-file coverage.info
	genhtml coverage.info --output-directory report/
	rm -f *.out *.log *.gcno *.gcov *.gcda coverage.info

clean:
	rm -rf *.txt *.o *.a *.out *.log *.gcno *.gcov *.gcda .clang-format coverage.info report/