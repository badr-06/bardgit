CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20 #-lpthread -pedantic -lsubunit -pthread

all: test

GCOVR_CFLAGS = -fprofile-arcs -ftest-coverage -fPIC
GTEST_LIB =  -lgtest -lgtest_main
TEST_SRC = test.cpp
TEST_RUN = run_tests

test: clean
	$(CC)  $(CFLAGS)  $(GCOVR_CFLAGS) $(TEST_SRC) -o $(TEST_RUN)  $(GTEST_LIB)
	./$(TEST_RUN)

gcov_report: test
	@printf "\n\e[1;35;107m RUN STACK TESTING  \e[31;0m \n"
	lcov -t "gcov_report" -o $(NAME)_coverage.info -c -d . --exclude '/usr/*' --exclude  $(TEST_SRC)
	genhtml -o gcov $(NAME)_coverage.info
	@printf "\n\e[1;35;107m END STACK TESTING   \e[31;0m \n"
	open ./gcov/index.html

clean:
	rm -f $(STL_LIB)
	rm -rf gcov
	rm -f *.*[oa]
	rm -f $(TEST_RUN)



.PHONY: all clean test rebuild

formated_code:
	clang-format --style=Google -n *.cpp
	clang-format --style=Google -n *.h
	clang-format --style=Google -n *.tpp
#правка убарть при провреке 
	clang-format --style=Google -i *.cpp
	clang-format --style=Google -i *.tpp
	clang-format --style=Google -i *.h

valgrind: clean  test
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN) $(GTEST_LIB)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cpp
#cppcheck -q --enable=all --inconclusive *.cpp

rebuild: clean all






