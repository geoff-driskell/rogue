SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = rogue
INCLUDE_PATHS = -I include
LIBRARY_PATHS = -L lib
COMPILER_FLAGS = -std=c++17 -Wall -g
LINKER_FLAGS = -lSDL2

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)