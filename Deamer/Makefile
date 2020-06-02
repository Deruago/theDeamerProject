INCLUDE_HEADER_DIR=./include
LIB_FILES=$(wildcard ./lib/*/*.cpp) \
		  $(wildcard ./lib/*.cpp)

TEST_FILE=DeamerTest.cpp

ARGS=-Wall
CC=clang++

all:
	$(CC) $(ARGS) $(LIB_FILES) -I $(INCLUDE_HEADER_DIR) $(TEST_FILE) -o Deamer
