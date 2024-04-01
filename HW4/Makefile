CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra 
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all --track-origins=yes
GTESTFLAGS = -lgtest -lgtest_main -pthread  
TARGET = prog
all: build
build: $(TARGET)
$(TARGET): BigInt.o main.cpp
	$(CXX) $(CXXFLAGS) BigInt.o main.cpp -o $(TARGET)
BigInt.o:
	$(CXX) $(CXXFLAGS) -c BigInt.cpp -o BigInt.o
run: build
	./$(TARGET)
test: testCompile
	./test
testCompile: BigInt.o gtest.cpp
	$(CXX) $(CXXFLAGS) BigInt.o gtest.cpp -o test $(GTESTFLAGS)
memory: testCompile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
clear:
	rm *.o $(TARGET) test

debug:
	gdb ./$(TARGET)
