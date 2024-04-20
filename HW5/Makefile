CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra 
VALGRIND_OPTS = --leak-check=full --show-leak-kinds=all --track-origins=yes
GTESTFLAGS = -lgtest -lgtest_main -pthread  
TARGET = prog
all: build
build: $(TARGET)
$(TARGET): Serializer.o main.cpp
	$(CXX) $(CXXFLAGS) Serializer.o main.cpp -o $(TARGET)
Serializer.o:
	$(CXX) $(CXXFLAGS) -c Serializer.cpp -o Serializer.o
run: build
	./$(TARGET)
test: testCompile
	./test
testCompile: Serializer.o gtest.cpp
	$(CXX) $(CXXFLAGS) Serializer.o gtest.cpp -o test $(GTESTFLAGS)
memory: testCompile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
clear:
	rm *.o $(TARGET) test
debug:
	gdb ./$(TARGET)
