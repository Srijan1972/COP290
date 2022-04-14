# Files to be compiled
OBJS=./src/main.cpp
# Compiler Name
CC=g++
# -w ignores all compiler warnings
COMPILER_FLAGS=-w
# Link to the libraries used
LINKER_FLAGS=-lSDL2 -lSDL2_image
# Name of the executable
OBJ_NAME=game.out

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)