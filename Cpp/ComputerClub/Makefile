CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror
TARGET = program

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) src/*.cpp -o $(TARGET)

install: $(TARGET)
	./$^ text.txt

test:
	$(CXX) $(CXXFLAGS) src/lib.cpp tests/test.cpp -o $@ -lgtest
	./$@

clean:
	rm -f $(TARGET) test
