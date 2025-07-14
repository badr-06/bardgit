CFLAGS = -Wall -Wextra -Werror -std=c++20
LFLAGS = -lcheck -pthread -lcheck_pic -lrt -lm -lsubunit -lncurses
QTFALGS = `pkg-config --cflags --libs Qt5Widgets`
BACK_T = brick_game/tetris/
BACK_S = brick_game/snake/
FRONT_D = gui/desktop/
FRONT_N = gui/cli/
TESTS = tests/
GTEST_LIB =  -lgtest -lgtest_main
CFILES = $(wildcard brick_game/tetris/*.c)
SNFILES = $(wildcard brick_game/snake/*.cpp)
TEST_FILES = $(wildcard tests/test_tetris.c)
TEST_SNAKE_FILES = $(wildcard tests/test_snake.cpp)


all: s21_tetris.a

s21_tetris.a:
	g++ -c $(CFLAGS) $(CFILES)
	ar rcs $@ *.o
	rm -f *.o

s21_snake.a:
	g++ -c $(CFLAGS) $(SNFILES)
	ar rcs $@ *.o
	rm -f *.o

install: s21_tetris.a s21_snake.a
	mkdir outfiles
	g++ $(CFLAGS) $(FRONT_N)game_tetris_cli.c $(FRONT_N)frontend.c s21_tetris.a -o outfiles/tetris_cli $(LFLAGS)
	g++ -fPIC $(CFLAGS) -Wno-deprecated-enum-enum-conversion $(FRONT_D)game_tetris_desktop.cpp $(FRONT_D)view_tetris.cpp $(FRONT_D)moc_view.cpp \
	s21_tetris.a -o outfiles/tetris_desktop $(QTFALGS)
	g++ $(CFLAGS) $(FRONT_N)game_snake_cli.cpp $(FRONT_N)frontend.c s21_snake.a -o outfiles/snake_cli $(LFLAGS)
	g++ -fPIC $(CFLAGS) -Wno-deprecated-enum-enum-conversion  $(FRONT_D)game_snake_desktop.cpp $(FRONT_D)view_snake.cpp $(FRONT_D)moc_view.cpp \
	s21_snake.a -o outfiles/snake_desktop $(QTFALGS)

uninstall:
	rm -rf outfiles

tests: test_tetris test_snake

test_tetris: s21_tetris.a
	g++ $(CFLAGS) $(TEST_FILES) s21_tetris.a -o test_tetris.out $(LFLAGS)

test_snake: s21_snake.a
	g++ $(CFLAGS) $(TEST_SNAKE_FILES) s21_snake.a -o test_snake.out $(GTEST_LIB)

gcov_report: gcov_report_tetris gcov_report_snake

gcov_report_tetris: CFLAGS += --coverage
gcov_report_tetris: test_tetris
	./test_tetris.out
	lcov -t "Tetris" -o coverage.info -c -d .
	lcov --extract coverage.info "*/brick_game/*" -o tetris_coverage.info
	genhtml tetris_coverage.info -o report_tetris
	rm -f *.out *.log *.gcno *.gcov *.gcda *.info test_tetris.out s21_tetris.a

gcov_report_snake: CFLAGS += --coverage
gcov_report_snake: test_snake
	./test_snake.out
	lcov -t "Snake" -o coverage.info -c -d .
	lcov --extract coverage.info "*/brick_game/*" -o snake_coverage.info
	genhtml snake_coverage.info -o report_snake
	rm -f *.out *.log *.gcno *.gcov *.gcda *.info test_snake.out s21_snake.a

dvi:
	doxygen Doxyfile

dist:
	zip -r brick_game_v2.zip ./*

clang:
	clang-format -n $(BACK_T)*.c $(BACK_T)*.h $(BACK_S)*.cpp $(BACK_S)*.h \
	$(FRONT_N)*.c $(FRONT_N)*.h $(FRONT_N)*.cpp $(FRONT_D)*.h $(FRONT_D)*.cpp \
	$(TESTS)*.c $(TESTS)*.cpp


clang_i:
	clang-format -i $(BACK_T)*.c $(BACK_T)*.h $(BACK_S)*.cpp $(BACK_S)*.h \
	$(FRONT_N)*.c $(FRONT_N)*.h $(FRONT_N)*.cpp $(FRONT_D)*.h $(FRONT_D)*.cpp \
	$(TESTS)*.c $(TESTS)*.cpp 

clang_copy:
	cp ../materials/linters/.clang-format .

valgrind: clean tests
	valgrind -s ./test_tetris.out
	valgrind -s ./test_snake.out

clean:
	rm -rf *.txt *.o *.a *.out *.log *.gcno *.gcov *.gcda .clang-format *.info report_snake report_tetris outfiles

clean_dvi:
	rm -rf docs