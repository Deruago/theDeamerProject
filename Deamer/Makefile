INCLUDE_HEADER_DIR=./include
LIB_FILES=$(wildcard ./lib/*/*.cpp) \
		  $(wildcard ./lib/*.cpp)

TEST_FILE=DeamerTest.cpp

OBJFILES=$(wildcard *.o)

ARGS=-Wall
CC=clang++

all: cleanAstNodeGen deamer
	$(CC) $(ARGS) $(LIB_FILES) -I $(INCLUDE_HEADER_DIR) $(TEST_FILE) -o Deamer
	
deamer:
	$(CC) $(ARGS) -c $(LIB_FILES) -I $(INCLUDE_HEADER_DIR)
	ar rcs ExportDeamer/libDeamer.a $(wildcard *.o)
	rm -f $(wildcard *.o)

compiler:
	flex lexer.l
	bison -d parser.y
	g++ -c parser.tab.c -o parser.tab.o
	g++ -c lex.yy.c -o lex.yy.o
	g++ parser.tab.o lex.yy.o -lfl -o myparser.out
	
cleanAstNodeGen:
	rm -f tests/AstNodes/*
	rm -f tests/Lexer/*
	rm -f tests/Parser/*
	rm -f lexer.l
	rm -f parser.y
	rm -f parser.tab.c
	rm -f parser.tab.o
	rm -f lex.yy.o
	rm -f parser.tab.h
	rm -f lex.yy.c
