# Makefile for Graph Algorithms Project

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Executables
MAIN_EXEC = Main
TEST_EXEC = test
HELPER_TEST_EXEC = test_helper

# Source files
SRC_FILES = graph.cpp algorithms.cpp helpers.cpp
HDR_FILES = graph.hpp algorithms.hpp helpers.hpp doctest.h

# Object files for main and test
MAIN_SRCS = $(SRC_FILES) main.cpp
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

TEST_SRCS = $(SRC_FILES) test.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

HELPER_TEST_SRCS = helpers.cpp test_helper.cpp
HELPER_TEST_OBJS = $(HELPER_TEST_SRCS:.cpp=.o)

# Default target
all: $(MAIN_EXEC) $(TEST_EXEC) $(HELPER_TEST_EXEC)

# Build main executable
$(MAIN_EXEC): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build unit test executable
$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build helper test executable
$(HELPER_TEST_EXEC): $(HELPER_TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Run programs
run_main:
	./$(MAIN_EXEC)

run_test:
	./$(TEST_EXEC)

run_helper_test:
	./$(HELPER_TEST_EXEC)

# Memory leak checks (if valgrind installed)
valgrind_main:
	valgrind --leak-check=full ./$(MAIN_EXEC)

valgrind_test:
	valgrind --leak-check=full ./$(TEST_EXEC)

valgrind_helper:
	valgrind --leak-check=full ./$(HELPER_TEST_EXEC)

# Clean build files
clean:
	rm -f *.o $(MAIN_EXEC) $(TEST_EXEC) $(HELPER_TEST_EXEC)
