.PHONY: all build clean rebuild cmake

all: build

cmake:
	cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Debug

build: cmake
	cmake --build build/

clean:
	rm -rf .vscode/ build/ CMakeLists.txt.user

rebuild: clean build