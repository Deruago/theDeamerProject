# Examples

This directory contains examples related to Deamer, examples are mostly part of tutorials found in the wiki.

## Building and running examples

As examples aren't available by default for CMake, you need to enable examples using the following option in cmake:

- -DEXAMPLES

Example of how one can build examples (starting from cloning deamer project):

- ```bash
  git clone --recursive https://github.com/Deruago/theDeamerProject.git
  cd ./theDeamerProject/Deamer
  mkdir build
  cd ./build
  ```

- ```bash
  cmake .. -DEXAMPLES=ON
  ```

- ```bash
  cmake --build . --target examples # build all examples
  ```

## cmake targets

Currently the following targets are available:

- ```bash
  examples			# build all examples
  ```

- ```bash
  simplelang_example	# build the simplelang, this example shows how to define a language
  ```

