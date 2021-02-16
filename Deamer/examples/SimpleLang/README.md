# SimpleLang example

This example will show you how one can create a simple language using Deamer, it will cover the Language Definition C++ format. And how one can write this in DLDL.

## SimpleLangGenerator

SimpleLangGenerator.cpp is the file that generates our compiler. It contains a LanguageDefinition (LD), which Deamer understands. Deamer will generate the compiler associated with that definition.

The code is structured in the following way:
1. Header includes
2. Initialisations
3. The language definition
4. Calling of tools, that can use the LD to generate specific programs. E.g. a compiler

## Defining our language

We use the standard macro set that is available from Deamer to define our LD. The macro's make it easier to write our LD, as they cover most of C++ related code (e.g. variable initialising).

We know several macro's, we will cover the most important ones:
- NODE()
- IGNORENODE()
- DELETENODE()
- TYPE()
- RULE()
- GROUPEDTYPE()
- GROUPTOKENS()

### Macro's explained
#### NODE
"NODE" is the same as an ordinary terminal symbol. Whenever you need a terminal symbol, you need to use the NODE macro.
NODE has several "abstractions", abstractions are used to abstract certain behaviour or optimise certain parts of a compiler. A simple example of such abstraction is "DELETENODE".
DELETENODE is used to delete a specific sequence, e.g. if you don't need newline characters then you may delete them, reducing the overhead in the following grammar.
IGNORENODE is another abstraction, this abstraction is however used whenever you don't need to memorize the value of the terminal symbol. It is an useful optimisation for symbols such as: '(', ')', '}'. But also for keywords such as: "int", "unsigned".

#### TYPE
"TYPE" is used to define nonterminal symbols with. You have abstracted variations of this macro, an imported one being: "GROUPEDTYPE".
GROUPEDTYPE is used to define types that function as "grouping" types, types which group multiple types together. This might be useful whenever you want to address multiple related terminal symbols.
Grouping of types can be done by first defining a groupedtype, and then grouping them with "GROUPTOKENS".

#### RULE
"RULE" is used to define production rules with, belonging to some non terminal symbol.