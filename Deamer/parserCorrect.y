%{
#include <iostream>
extern "C" void yyerror(char* s);
extern "C" int yyparse();
extern "C" FILE* yyin;
int yylex();
%}

%token VARNAME
%token FLOAT
%token DOUBLE
%token INT
%token CHAR
%token STRING
%token STRING_TYPE
%token EQUAL
%token NOTCOMP
%token COMPARE
%token DECIMAL
%token NUMBER
%token MIN
%token DIV
%token MULT
%token PLUS
%token SEMICOLON

%type <DeamerNode> VARNAME
%type <DeamerNode> FLOAT
%type <DeamerNode> DOUBLE
%type <DeamerNode> INT
%type <DeamerNode> CHAR
%type <DeamerNode> STRING
%type <DeamerNode> STRING_TYPE
%type <DeamerNode> EQUAL
%type <DeamerNode> NOTCOMP
%type <DeamerNode> COMPARE
%type <DeamerNode> DECIMAL
%type <DeamerNode> NUMBER
%type <DeamerNode> MIN
%type <DeamerNode> DIV
%type <DeamerNode> MULT
%type <DeamerNode> PLUS
%type <DeamerNode> SEMICOLON
%type <DeamerType> PROG
%type <DeamerType> STMTS
%type <DeamerType> STMT
%type <DeamerType> VAR_EXPR
%type <DeamerType> VAR_INIT
%type <DeamerType> EXPRS
%type <DeamerType> EXPR
%type <DeamerType> COND
%type <DeamerType> DATATYPE

%union{
    char DeamerNode[1024];
    char DeamerType[2048];
}



%%


PROG:
      STMTS {
    }
;

STMTS:
      STMT SEMICOLON STMTS {
        std::cout << $2;
    }
    | {
    }
;

STMT:
      EXPR {
    }
;

VAR_EXPR:
      VAR_INIT {
    }
;

VAR_INIT:
      DATATYPE VARNAME EQUAL EXPRS {
        std::cout << $2;
        std::cout << $3;
    }
;

EXPRS:
      EXPR {
    }
    | EXPR COND EXPRS {
    }
;

EXPR:
      VAR_EXPR {
    }
    | STRING_TYPE {
        std::cout << $1;
    }
    | DECIMAL {
        std::cout << $1;
    }
    | NUMBER {
        std::cout << $1;
    }
;

COND:
      DIV {
        std::cout << $1;
    }
    | MULT {
        std::cout << $1;
    }
    | MIN {
        std::cout << $1;
    }
    | PLUS {
        std::cout << $1;
    }
;

DATATYPE:
      FLOAT {
        std::cout << $1;
    }
    | DOUBLE {
        std::cout << $1;
    }
    | INT {
        std::cout << $1;
    }
    | CHAR {
        std::cout << $1;
    }
    | STRING {
        std::cout << $1;
    }
;


%%


void yyerror(char *s)
{
    printf("Syntax error on line %s", s);
}

