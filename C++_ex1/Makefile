# Makefile for Graph Algorithms Project

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executables
MAIN_EXEC = Main
TEST_EXEC = test

# Source files
SRCS = graph.cpp algorithms.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
TEST_SRCS = graph.cpp algorithms.cpp test.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default rule
all: $(MAIN_EXEC) $(TEST_EXEC)

# Compile Main
$(MAIN_EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXEC) $(OBJS)

# Compile Tests
$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_OBJS)

# Run main program
run_main:
	./$(MAIN_EXEC)

# Run unit tests
run_test:
	./$(TEST_EXEC)

# Run memory leak check
valgrind:
	valgrind --leak-check=full ./$(TEST_EXEC)

# Clean unnecessary files
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(MAIN_EXEC) $(TEST_EXEC)
