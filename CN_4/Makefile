#######################################
# 	Makefile for the ping program.    #
#	Made by: Roy Simanovich.          #
#	Last modified: 13/02/2024.        #
#	For: Computer Networks course.    #
#	Free to use and distribute.       #
#######################################

# Use the gcc compiler.
CC = gcc

# Flags for the compiler. Can also use -g for debugging.
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic

# Linker flags (e.g., math library).
LDFLAGS = -lm

# Command to remove files.
RM = rm -f

# Header files.
HEADERS = ping.h

# Source files.
SOURCES = ping.c 

# Executable files.
EXECS = ping 

# IP address to ping.
IP = 1.1.1.1

# Phony targets - targets that are not files but commands to be executed by make.
.PHONY: all default clean runp runsp

# Default target - compile everything and create the executables and libraries.
all: $(EXECS) traceroute

traceroute: traceroute.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Alias for the default target.
default: all

############
# Programs #
############

# Compile the ping program.
$(EXECS): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

################
# Run programs #
################

# Run ping program in sudo mode.
runp: $(EXECS)
	sudo ./$< -a $(IP) -t 4 -c 4

################
# System Trace #
################

# Run the ping program with system trace (sudo mode).
runsp: $(EXECS)
	sudo strace ./$< -a $(IP) -t 4 -c 4

################
# Object files #
################

# Compile all the C files into object files.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#################
# Cleanup files #
#################

# Remove all the object files, shared libraries and executables.
clean:
	$(RM) *.o *.so $(EXECS)