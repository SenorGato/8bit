#OBJS defines files to compile
OBJS = main.cpp  
CC = g++
COMPILER_FLAGS = -g -Wall -Wextra -Wpedantic -std=c++17 $(shell pkg-config --cflags SDL2_image) $(shell pkg-config --cflags SDL2_ttf)
LINKER_FLAGS = $(shell pkg-config --libs SDL2_image) $(shell pkg-config --libs SDL2_ttf) 
OBJ_NAME = menu 

all : $(OBJS) 
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
