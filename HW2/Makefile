CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra 
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all --track-origins=yes
GTESTFLAGS = -lgtest -lgtest_main -pthread  
TARGET = prog
all: build
build: $(TARGET)
$(TARGET): TokenParser.o main.cpp
	$(CXX) $(CXXFLAGS) TokenParser.o main.cpp -o $(TARGET)
TokenParser.o:
	$(CXX) $(CXXFLAGS) -c TokenParser.cpp -o TokenParser.o
run: build
	./$(TARGET)
test: testCompile
	./test
testCompile: TokenParser.o gtest.cpp
	$(CXX) $(CXXFLAGS) TokenParser.o gtest.cpp -o test $(GTESTFLAGS)
memory: testCompile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
clear:
	rm *.o $(TARGET) test
