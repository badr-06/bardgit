CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++20 -lpthread -pedantic -lsubunit -pthread

GCOVR_CFLAGS = -fprofile-arcs -ftest-coverage -fPIC
GTEST_LIB =  -lgtest -lgtest_main
TEST_SRC = main_test.cpp
TEST_RUN = run_tests

all : test

test: clean
	$(CC)  $(CFLAGS)  $(GCOVR_CFLAGS) $(TEST_SRC) -o $(TEST_RUN)  $(GTEST_LIB)
	./$(TEST_RUN)

gcov_report: test
	@printf "\n\e[1;35;107m RUN QUEUE TESTING  \e[31;0m \n"
	mkdir report
	gcovr -r . --html --html-details  -o ./report/coverage_report.html
	@printf "\n\e[1;35;107m END QUEUE TESTING   \e[31;0m \n"


clean:
	rm -rf gcov
	rm -f *.*[oa]
	rm -f $(TEST_RUN)
	rm -rf report

clang_cp:
	cp ../../materials/linters/.clang-format .clang-format

clang_def:
	clang-format -n *.hpp
	clang-format -n *.h
	clang-format -n *.cpp
	clang-format -n ./s21_*/*.tpp
	clang-format -n ./s21_*/*.h
	clang-format -n ./s21_*/*.cpp
	clang-format -n ./s21_*/*.hpp
	
	clang-format -i *.h
	clang-format -i *.cpp
	clang-format -i *.hpp
	clang-format -i ./s21_*/*.cpp
	clang-format -i ./s21_*/*.tpp
	clang-format -i ./s21_*/*.h
	clang-format -i ./s21_*/*.hpp

.PHONY: all clean test gcov_report rebuild valgrind

valgrind:
	valgrind --leak-check=full --track-origins=yes ./$(TEST_RUN) $(GTEST_LIB)

rebuild: clean all

