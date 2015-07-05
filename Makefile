OBJS = main.cpp jloader.cpp controller.cpp

CC = g++

COMPILER_FLAGS = -Wall -std=c++11 `sdl2-config --cflags`

LINKER_FLAGS = -lSDL2_image -ldl -lpng -ljpeg -lz `sdl2-config --libs sdl2`

OBJ_NAME = demo_game

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

