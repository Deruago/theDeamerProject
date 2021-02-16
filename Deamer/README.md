# Deamer, Compiler Generator

## Overview

Deamer is a compiler generator which generates the front- and mid-end of a compiler. Deamer has several specialized definitions to generate a compiler. So far the following definitions can be used:

- Lexer definition
- Parser definition

The output compiler can be any combination of lexer generators and parser generators, e.g. you can generate a compiler which uses the flex and bison generators for the lexer and parser part.

All the definitions you can use in Deamer are also supported by [DLDL](https://github.com/Deruago/DLDL). [DLDL](https://github.com/Deruago/DLDL) is a language which generates C++ code for Deamer, allowing you to more easily define languages. [DLDL](https://github.com/Deruago/DLDL) will be supported with each new definition. It is recommended to use [DLDL](https://github.com/Deruago/DLDL) instead of writing the C++ code on your own for Deamer, as it automates a lot of processes.

## Installing Deamer

Deamer uses cmake to build the source code, it is thus required that you have cmake. Instructions on how to get cmake can be found [here](https://cmake.org/install/).

When you have cmake installed, you can run the following commands to install Deamer:

```bash
# clone the repo
git clone --recursive https://github.com/Deruago/theDeamerProject.git

# move to the Deamer project
cd ./theDeamerProject
cd ./Deamer

# create a build directory
mkdir build
cd ./build

# generate cmake files, and build and install Deamer
cmake ..
sudo cmake --build . --target install
```

### Potential prerequisites

Deamer can use external lexer and parser generators, and will do this by default (flex and bison). It is thus recommended to install the desired generators on your linux device.

available lexer-generators:

- Flex

available parser-generators:

- Bison

Deamer currently doesn't have an internal lexer-generator or parser-generator, this will however be added in later versions of Deamer.

#### Installing flex

```bash
sudo apt install flex
```

#### Installing bison++

```bash
sudo apt install bison++
```



## Examples

### SimpleLang

SimpleLang example is more explained in the example directory. This part is mostly for illustrating how one can use Deamer.

#### Example of defining a language in Deamer

```c++
#include "Deamer/LanguageGen/LanguageGen.h"
#include "Deamer/LanguageAnalyzer/LanguageOptimiser.h"
#include "Deamer/LanguageAnalyzer/LanguagePrinter/LanguageDefinitionPrinter.h"
#include "Deamer/LanguageGen/LanguageDefMacros.h"
#include "Deamer/AstGen/AstGen.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstBuilderType.h"
#include "Deamer/ThreatAnalyzer/Printer/ThreatPrinter.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefinitionThreatAnalyzer.h"
#include <iostream>
using namespace deamer;

int main()
{
    #ifdef currentLangDef
    #undef currentLangDef
    #endif
    #define currentLangDef language_definition_builder

    LanguageDefinitionBuilder language_definition_builder = LanguageDefinitionBuilder();
    language_definition_builder.SetTypeContinuation(TypeContinuation_t::vector);

    DELETENODE(ESCAPE_CHARACTERS, "[\\n\\r\\t ]+");
    IGNORENODE(LEFT_CURLY_BRACKET, "[(]");
    IGNORENODE(RIGHT_CURLY_BRACKET, "[)]");
    IGNORENODE(LEFT_BRACKET, "[{]");
    IGNORENODE(RIGHT_BRACKET, "[}]");
    IGNORENODE(EQUAL, "[=]");
    IGNORENODE(SEMICOLON, "[;]");
    IGNORENODE(FUNCTION_DECLARATION, "def");
    IGNORENODE(VARIABLE_DECLARATION, "var");
    NODE(VARNAME, "[a-zA-Z_]+[a-zA-Z_0-9]*");
    NODE(NUMBER, "[0-9]+");
    NODE(DECIMAL, "[0-9]+[\\.][0-9]+");
    NODE(STRING, "[\"][.]*[\"]");
    TYPE(prog);
    TYPE(stmts);
    GROUPEDTYPE(stmt);
    TYPE(variable_initialisation);
    TYPE(function_initialisation);
    TYPE(block);

    RULE(prog, stmts);
    RULE(stmts, stmt, stmts);
    RULE(stmts, EMPTY);
    GROUPTOKENS(stmt, variable_initialisation, function_initialisation);
    RULE(variable_initialisation, VARIABLE_DECLARATION, VARNAME, EQUAL, NUMBER, SEMICOLON);
    RULE(variable_initialisation, VARIABLE_DECLARATION, VARNAME, EQUAL, STRING, SEMICOLON);
    RULE(variable_initialisation, VARIABLE_DECLARATION, VARNAME, EQUAL, DECIMAL, SEMICOLON);
    RULE(variable_initialisation, VARIABLE_DECLARATION, VARNAME, EQUAL, VARNAME, SEMICOLON);
    RULE(function_initialisation, FUNCTION_DECLARATION, VARNAME, LEFT_CURLY_BRACKET, RIGHT_CURLY_BRACKET, block);
    RULE(block, LEFT_BRACKET, stmts, RIGHT_BRACKET);
}
```

#### Example of defining a language in DLDL

```DLDL
//////////////////////////////////////
/ This is part of an example         /
/ The language is called SimpleLang  /
//////////////////////////////////////



/ deleted sequences
DELETE: ESCAPE_CHARACTERS [\n\r\t\s]+

/ Symbols
IGNORE: LEFT_CURLY_BRACKET  [(]
IGNORE: RIGHT_CURLY_BRACKET [)]
IGNORE: LEFT_BRACKET        [{]
IGNORE: RIGHT_BRACKET       [}]
IGNORE: EQUAL               [=]
IGNORE: SEMICOLON           [;]

/ Declarations
IGNORE: FUNCTION_DECLARATION def
IGNORE: VARIABLE_DECLARATION var

/ Data terminals
TERMINAL: VARNAME [a-zA-Z_]+[a-zA-Z_0-9]*
TERMINAL: NUMBER  [0-9]+
TERMINAL: DECIMAL [0-9]+[\.][0-9]+
TERMINAL: STRING  [\"][.]*[\"]

/ Context free grammar
prog
	stmts

stmts
	stmt stmts
	EMPTY

GROUP: stmt variable_initialisation function_initialisation

variable_initialisation
	VARIABLE_DECLARATION VARNAME EQUAL NUMBER SEMICOLON
	VARIABLE_DECLARATION VARNAME EQUAL STRING SEMICOLON
	VARIABLE_DECLARATION VARNAME EQUAL DECIMAL SEMICOLON
	VARIABLE_DECLARATION VARNAME EQUAL VARNAME SEMICOLON

function_initialisation
	FUNCTION_DECLARATION VARNAME LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET block

block
	LEFT_BRACKET stmts RIGHT_BRACKET

/
```

## Contributing

You may contribute in varies ways:

- Use Deamer
- Report bugs
- Help fix bugs
- Help maintain the project



