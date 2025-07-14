CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20 -lpthread -pedantic -lsubunit -pthread

GCOVR_CFLAGS = -fprofile-arcs -ftest-coverage -fPIC
GTEST_LIB =  -lgtest -lgtest_main
TEST_SRC = set_test.cpp
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

clang_google:
	clang-format --style=Google -i *.tpp
	clang-format --style=Google -i *.cpp
	clang-format --style=Google -i *.h

clang_def:
	clang-format -i *.tpp
	clang-format -i *.h
	clang-format -i *.cpp

.PHONY: all clean test gcov_report rebuild valgrind formated_code cppcheck



valgrind:
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN) $(GTEST_LIB)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cpp
	#cppcheck -q --enable=all --inconclusive *.cpp

rebuild: clean all
