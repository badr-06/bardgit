
all: install

# Создает директорию build и собирает проект
install:
	mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build .

clean:
	rm -rf build