# Makefile for SquareMat project

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Executable name
TARGET = squaremat_run

# Source files
SRCS = main.cpp SquareMat.cpp

# Header files (optional for dependencies)
HEADERS = SquareMat.hpp

# Build rule
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean compiled files
clean:
	rm -f $(TARGET)
