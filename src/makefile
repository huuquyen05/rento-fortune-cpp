# Makefile template for CSC3002

# Custom Macros:
PROGRAM = game

# Find all .cpp files and convert them to .o files (object files)
SOURCES = chatbox.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# SFML include and lib paths
SFML_INCLUDE = -IC:/SFML-2.6.2/include
SFML_LIB = -L C:/SFML-2.6.2/lib

# SFML libraries to link against
SFML_LIBS = -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main

# Compiler flags
CFLAGS = -std=c++17 $(SFML_INCLUDE)

# Compiler and linker
CC = g++

# Main target: Build the executable
all: $(PROGRAM)

# Linking object files to create the executable
$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(SFML_LIB) $(SFML_LIBS)

# Rule for creating object files from .cpp files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Custom echo rule for printing a string to the console
echo:
	@echo I love CSC3002 !!!!! 

# Clean up all the object and executable files
clean:
	rm -f $(OBJECTS) $(PROGRAM)