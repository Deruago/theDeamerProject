# Tests

This directory is used for testing. Testing is done using googletests, and can be run via cmake.

# Guidelines

Each unit test is at the same hierachical place as the class it is testing. Meaning the following:
- We want to test class: include/Deamer/Types/Vector/SmallVector.h
- then we need to create an unit test class at place: tests/Types/Vector/SmallVector.cpp