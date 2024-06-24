CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra 
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all --track-origins=yes
GTESTFLAGS = -lgtest -lgtest_main -pthread  
TARGET = prog
all: build
build: $(TARGET)
$(TARGET): Format.h main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)
run: build
	./$(TARGET)
test: testCompile
	./test
testCompile: Format.h gtest.cpp
	$(CXX) $(CXXFLAGS) gtest.cpp -o test $(GTESTFLAGS)
memory: testCompile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
clear:
	rm *.o $(TARGET) test
debug:
	gdb ./$(TARGET)
