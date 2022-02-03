#OBJS defines files to compile
OBJS = testbase.cpp 
CC = g++
COMPILER_FLAGS = -w -g
LINKER_FLAGS = -lSDL2 -lSDL2_ttf 
OBJ_NAME = menu 

all : $(OBJS) 
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
