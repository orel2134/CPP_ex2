  # orel2744@gmail.com

# makefile for graph algorithms project 


# compiler and flags

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17


# source and header files

SRC = graph.cpp algorithms.cpp helpers.cpp
HDR = graph.hpp algorithms.hpp helpers.hpp doctest.h


# test files

TEST_ALGO_SRC = test_algo.cpp
TEST_GRAPH_SRC = test_graph.cpp
TEST_HELPER_SRC = test_helper.cpp


# executables

MAIN_EXEC = Main
TEST_ALGO_EXEC = test_algo
TEST_GRAPH_EXEC = test_graph
TEST_HELPER_EXEC = test_helper


# object files

MAIN_OBJS = $(SRC:.cpp=.o) main.o
TEST_ALGO_OBJS = $(SRC:.cpp=.o) test_algo.o
TEST_GRAPH_OBJS = graph.o test_graph.o
TEST_HELPER_OBJS = helpers.o test_helper.o


# build rules


all: $(MAIN_EXEC) $(TEST_ALGO_EXEC) $(TEST_GRAPH_EXEC) $(TEST_HELPER_EXEC)

$(MAIN_EXEC): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_ALGO_EXEC): $(TEST_ALGO_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_GRAPH_EXEC): $(TEST_GRAPH_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_HELPER_EXEC): $(TEST_HELPER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) -c $<


# run targets


run_main:
	./$(MAIN_EXEC)

run_algo_tests:
	./$(TEST_ALGO_EXEC)

run_graph_tests:
	./$(TEST_GRAPH_EXEC)

run_helper_tests:
	./$(TEST_HELPER_EXEC)

run_all_tests: run_algo_tests run_graph_tests run_helper_tests


# valgrind targets

valgrind_algo:
	valgrind --leak-check=full ./$(TEST_ALGO_EXEC)

valgrind_graph:
	valgrind --leak-check=full ./$(TEST_GRAPH_EXEC)

valgrind_helper:
	valgrind --leak-check=full ./$(TEST_HELPER_EXEC)

valgrind_all: valgrind_algo valgrind_graph valgrind_helper


# clean target

clean:
	rm -f *.o $(MAIN_EXEC) $(TEST_ALGO_EXEC) $(TEST_GRAPH_EXEC) $(TEST_HELPER_EXEC)
