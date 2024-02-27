CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra 
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all --track-origins=yes
GTESTFLAGS = -lgtest -lgtest_main -pthread  
TARGET = prog
all: build
build: $(TARGET)
$(TARGET): Allocator.o main.cpp
	$(CXX) $(CXXFLAGS) Allocator.o main.cpp -o $(TARGET)
Allocator.o:
	$(CXX) $(CXXFLAGS) -c Allocator.cpp -o Allocator.o
run: build
	./$(TARGET)
test: testCompile
	./test
testCompile: Allocator.o gtest.cpp
	$(CXX) $(CXXFLAGS) Allocator.o gtest.cpp -o test $(GTESTFLAGS)
memory: testCompile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
clear:
	rm *.o $(TARGET) test