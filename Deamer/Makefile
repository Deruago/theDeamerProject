INCLUDE_HEADER_DIR=./include
LIB_FILES=$(wildcard ./lib/*/*.cpp) \
		  $(wildcard ./lib/*.cpp)

TEST_FILE=DeamerTest.cpp

ARGS=-Wall
CC=clang++

all: cleanAstNodeGen
	$(CC) $(ARGS) $(LIB_FILES) -I $(INCLUDE_HEADER_DIR) $(TEST_FILE) -o Deamer
	
cleanAstNodeGen:
	rm -f AstNode*
	rm -f AstTree*
	rm -f tests/AstNode*
	rm -f tests/AstTree*
