CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20 -lpthread -pedantic -lsubunit -pthread

GCOVR_CFLAGS = -fprofile-arcs -ftest-coverage -fPIC
GTEST_LIB =  -lgtest -lgtest_main
TEST_SRC = multiset_test.cpp
TEST_RUN = run_tests

all : test

test: clean
	$(CC)  $(CFLAGS)  $(GCOVR_CFLAGS) $(TEST_SRC) -o $(TEST_RUN)  $(GTEST_LIB)
	./$(TEST_RUN)

gcov_report: test
	@printf "\n\e[1;35;107m RUN QUEUE TESTING  \e[31;0m \n"
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d . --exclude '/usr/*' --exclude  $(TEST_SRC)
	genhtml -o gcov $(NAME)_coverage.info
	@printf "\n\e[1;35;107m END QUEUE TESTING   \e[31;0m \n"

clean:
	rm -rf gcov
	rm -f *.*[oa]
	rm -f $(TEST_RUN)

clang_cp:
	cp ../../materials/linters/.clang-format .clang-format

.PHONY: all clean test gcov_report rebuild valgrind

valgrind:
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN) $(GTEST_LIB)

rebuild: clean all

