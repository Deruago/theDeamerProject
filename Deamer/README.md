# Deamer, Compiler Generator

## Overview

Deamer CC is a compiler and ecosystem generator. Via specialized definitions Deamer is capable of generating complete compilers and complete ecosystems (such as: formatting, refactoring, syntax highlighters, formatters, etc).
Using specialized definitions one can specify languages ranging from multi compilers to simple DSL's.

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

For examples see the development branch.

## Contributing

You may contribute in varies ways:

- Use Deamer
- Report bugs
- Help fix bugs
- Help maintain the project



