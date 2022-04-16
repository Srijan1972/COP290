# Files to be compiled
OBJS = ./src/main.cpp
# Compiler Name
CC = g++
# -w ignores all compiler warnings
COMPILER_FLAGS = -w
# Link to the libraries used
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer
# Name of the executable
OBJ_NAME = duel

# Command to generate the executable
all:
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

# Command to remove the executable
clean:
	rm $(OBJ_NAME)
	clear

# For testing purposes
test:
	make && ./$(OBJ_NAME)

# Regenerate the executable
again:
	make clean && make
