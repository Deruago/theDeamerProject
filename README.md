[![Codacy Badge](https://app.codacy.com/project/badge/Grade/d46f28fda6e949578efd991af7c045bd)](https://www.codacy.com/gh/Deruago/theDeamerProject/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Deruago/theDeamerProject&amp;utm_campaign=Badge_Grade)

[![CMake](https://github.com/Deruago/theDeamerProject/actions/workflows/cmake.yml/badge.svg?branch=development)](https://github.com/Deruago/theDeamerProject/actions/workflows/cmake.yml)[![](https://tokei.rs/b1/github/Deruago/theDeamerProject)](https://github.com/Deruago/theDeamerProject)

# The DeamerProject

This directory and subdirectories contain source code and documentation regarding the DeamerProject. The goal of this readme file is to briefly explain what the "DeamerProject" is.

## Getting started with the DeamerProject

### Overview

Welcome to the DeamerProject!

DeamerProject exists of multiple components that as whole count as the DeamerProject. The core of this project is "Deamer", Deamer is an infrastructure for compiler and ecosystem generation. This means that you can generate complete compilers, and complete ecosystems for your compilers (syntax highlighting, refactoring, auto-completion, etc).

Deamer is a definition based infrastructure, allowing extensions to easily reuse existing definitions. This way Deamer is capable of supporting a lot of extensions.

Deamer-Tools included in the Deamer Project: [Deamer](https://github.com/Deruago/theDeamerProject), Deamer-lang, [DLDL](https://github.com/Deruago/DLDL), DQSL, DCPP, [DST](https://github.com/Deruago/DeamerStringTemplate).

## Getting the source code and building DeamerProject

Deamer uses cmake for building the source code. You can install cmake [here](https://cmake.org/install/) by following the instructions.
When you have cmake, installing the project is as simple as using the following commands:

- ``````bash
  git clone --recursive https://github.com/Deruago/theDeamerProject.git
  cd ./theDeamerProject
  ``````

- ``````bash
  cd ./Deamer
  ``````

- ``````bash
  mkdir build
  cd ./build
  ``````

- ```bash
  cmake ..
  sudo cmake --build . --target install
  ```

### Cmake

Cmake is used for installing, building, and running the tests. Currently the following targets can be used for cmake:

- ```bash
  examples		# builds all the examples, see the examples directory for more information
  ```

- ``````bash
  install			# installs the library
  ``````

- ``````bash
  Deamer			# builds the library
  ``````

- ``````bash
  build_and_test	# build and run the tests
  ``````

- ``````bash
  test			# run the last build tests
  ``````

## Examples

Go to the development branch, or go visit the wiki.

We are currently busy documenting everything, so if you are missing something feel free to report it.

## Deamer v1 vs Deamer v2

Deamer v1 was the original infrastructure, it had been redesigned and reimplemented as Deamer v2.

Please use Deamer v2. All tools currently available for Deamer v2 can be found [here](https://github.com/Deruago/theDeamerProject/wiki/Deamer-v2:-Deamer-tool-support).

## License

DeamerProject is distributed under the [GNU General Public License](http://www.gnu.org/copyleft/gpl.html) (GPL, or “free software”).

This license grants people a number of freedoms:

- You are free to use DeamerProject , for any purpose
- You are free to distribute DeamerProject 
- You can study how DeamerProject works and change it
- You can distribute changed versions of DeamerProject 

The GPL strictly aims at protecting these freedoms, requiring everyone  to share their modifications when they also share the software in  public. That aspect is commonly referred to as [Copyleft](http://en.wikipedia.org/wiki/Copyleft).

Some parts of Deamer are licensed under a different license. Whenever a part is under a different license, this will be communicated through a README.MD

The "extern" directory is not covered under this license.

### Contributing

Feel free to contribute to the DeamerProject! But there are some things to note:

- All contributions through pull-requests, issues, or otherwise, you accept to release your contribution to the license terms described in [LICENSE](https://github.com/Deruago/theDeamerProject/blob/master/LICENSE).
- If a contributor wants to further state their copyright on any of their contributions, they can do so by indicating their copyright in the commit message.
