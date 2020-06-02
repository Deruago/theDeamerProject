#ifndef DEAMER_LANGUAGEGEN_LANGUAGEGEN_CONSTANTS_H
#define DEAMER_LANGUAGEGEN_LANGUAGEGEN_CONSTANTS_H

typedef enum LexerType_s
{
    dlex, //Deamer lexer. Currently unsupported
    flex
} LexerType_t;

typedef enum ParserType_s
{
    dparse, //Deamer parser. Currently unsupported
    bison
} ParserType_t;

#endif //DEAMER_LANGUAGEGEN_LANGUAGEGEN_CONSTANTS_H