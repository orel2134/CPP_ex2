# Makefile for SquareMat project

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Executable names
MAIN_EXEC = squaremat_run
TEST_EXEC = test_squarmemat

# Source files
MAIN_SRCS = main.cpp SquareMat.cpp
TEST_SRCS = test_Squaremat.cpp SquareMat.cpp

# Header files
HEADERS = SquareMat.hpp

# Build main executable
$(MAIN_EXEC): $(MAIN_SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(MAIN_SRCS) -o $(MAIN_EXEC)

# Build test executable
$(TEST_EXEC): $(TEST_SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $(TEST_EXEC)

# Run main
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Run valgrind memory check (requires valgrind to be installed)
valgrind: $(TEST_EXEC)
	valgrind --leak-check=full ./$(TEST_EXEC)

# Clean compiled files
clean:
	rm -f $(MAIN_EXEC) $(TEST_EXEC)