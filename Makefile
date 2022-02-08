#OBJS defines files to compile
OBJS = main.cpp Menu.cpp 
CC = g++
COMPILER_FLAGS = -g -Wall -Wextra -Wpedantic -std=c++17
LINKER_FLAGS = -lSDL2 -lSDL2_ttf 
OBJ_NAME = menu 

all : $(OBJS) 
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
