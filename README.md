[![CMake](https://github.com/Deruago/theDeamerProject/actions/workflows/cmake.yml/badge.svg?branch=development)](https://github.com/Deruago/theDeamerProject/actions/workflows/cmake.yml)

# The DeamerProject

This directory and subdirectories contain source code and documentation regarding the DeamerProject. The goal of this readme file is to briefly explain what the "DeamerProject" is.

## Getting started with the DeamerProject

### Overview

Welcome to the DeamerProject!

DeamerProject exists of multiple components that as whole count as the DeamerProject. The core of this project is "Deamer", Deamer is a compiler generator used to generate the front-end and mid-end of compilers (and a whole lot more). The DeamerProject include tools for language generation, language processing, language testing, language optimisations, and tools to support people with RSI.

Tools included are: [Deamer](https://github.com/Deruago/theDeamerProject), Deamer-lang, [DLDL](https://github.com/Deruago/DLDL), DQSL, DCPP.

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
