# Makefile for Graph Algorithms Project

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Executable names
MAIN_EXEC = Main
TEST_EXEC = test_algo
GRAPH_TEST_EXEC = test_graph
HELPER_TEST_EXEC = test_helper

# Source files
SRC = graph.cpp algorithms.cpp helpers.cpp
HDR = graph.hpp algorithms.hpp helpers.hpp doctest.h

# Object files
MAIN_OBJS = $(SRC:.cpp=.o) main.o
TEST_ALGO_OBJS = $(SRC:.cpp=.o) test_algo.o
TEST_GRAPH_OBJS = graph.o test_graph.o
TEST_HELPER_OBJS = helpers.o test_helper.o

# Default target - build all
all: $(MAIN_EXEC) $(TEST_EXEC) $(GRAPH_TEST_EXEC) $(HELPER_TEST_EXEC)

# Main program
$(MAIN_EXEC): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Algorithm tests
$(TEST_EXEC): $(TEST_ALGO_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Graph tests
$(GRAPH_TEST_EXEC): $(TEST_GRAPH_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Helper tests
$(HELPER_TEST_EXEC): $(TEST_HELPER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# --------------------------
# Run individual executables
# --------------------------
run_main:
	./$(MAIN_EXEC)

run_algo_tests:
	./$(TEST_EXEC)

run_graph_tests:
	./$(GRAPH_TEST_EXEC)

run_helper_tests:
	./$(HELPER_TEST_EXEC)

# --------------------------
# Run all tests at once
# --------------------------
run_all_tests: run_algo_tests run_graph_tests run_helper_tests

# --------------------------
# Run with valgrind
# --------------------------
valgrind_main:
	valgrind --leak-check=full ./$(MAIN_EXEC)

valgrind_algo:
	valgrind --leak-check=full ./$(TEST_EXEC)

valgrind_graph:
	valgrind --leak-check=full ./$(GRAPH_TEST_EXEC)

valgrind_helper:
	valgrind --leak-check=full ./$(HELPER_TEST_EXEC)

valgrind_all: valgrind_algo valgrind_graph valgrind_helper

# --------------------------
# Clean everything
# --------------------------
clean:
	rm -f *.o $(MAIN_EXEC) $(TEST_EXEC) $(GRAPH_TEST_EXEC) $(HELPER_TEST_EXEC)
