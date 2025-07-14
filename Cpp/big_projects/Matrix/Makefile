# Цель по умолчанию
all: s21_matrix_oop.a test

# Создание статической библиотеки
s21_matrix_oop.a: obj/s21_matrix.o obj/function.o
	ar rcs s21_matrix_oop.a obj/s21_matrix.o obj/function.o
	rm -rf obj/

# Сборка объектных файлов
obj/s21_matrix.o:
	@mkdir -p obj
	g++ -Wall -Wextra -Werror -std=c++11 -c s21_matrix.cpp -o obj/s21_matrix.o

obj/function.o:
	@mkdir -p obj
	g++ -Wall -Wextra -Werror -std=c++11 -c function.cpp -o obj/function.o

# Сборка тестов
test: s21_matrix_oop.a
	g++ -Wall -Wextra -Werror -std=c++11 -o test test.cpp -L. -l:s21_matrix_oop.a -lgtest -lgtest_main -lpthread
	./test

# проверка на стиль кода
clang_format: 
	cp ../materials/linters/.clang-format .
	clang-format -n *.cpp *.hpp

# Проверка на утечки памяти
valgrind:
	valgrind  -s --leak-check=full ./test 

# Очистка
clean:
	rm *.a test
