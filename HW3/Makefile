CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra 
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all --track-origins=yes
GTESTFLAGS = -lgtest -lgtest_main -pthread  
TARGET = prog
all: build
build: $(TARGET)
$(TARGET): Matrix.o main.cpp
	$(CXX) $(CXXFLAGS) Matrix.o main.cpp -o $(TARGET)
TokenParser.o:
	$(CXX) $(CXXFLAGS) -c Matrix.cpp -o Matrix.o
run: build
	./$(TARGET)
test: testCompile
	./test
testCompile: Matrix.o gtest.cpp
	$(CXX) $(CXXFLAGS) Matrix.o gtest.cpp -o test $(GTESTFLAGS)
memory: testCompile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
clear:
	rm *.o $(TARGET) test
