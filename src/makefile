# Custom Macros:
PROGRAM = main

# Find all .cpp files and convert them to .o files (object files)
SOURCES = dice.cpp game.cpp main.cpp player.cpp property.cpp slot.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Compiler flags
CFLAGS = -std=c++17

# Compiler and linker
CC = g++

# Main target: Build the executable
all: $(PROGRAM)

# Linking object files to create the executable
$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for creating object files from .cpp files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Custom echo rule for printing a string to the console
echo:
	@echo I love CSC3002!!!!!

# Clean up all the object and executable files
clean:
	rm -f $(OBJECTS) $(PROGRAM)
