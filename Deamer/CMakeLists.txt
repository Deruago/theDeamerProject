cmake_minimum_required(VERSION 3.11)

project(Deamer VERSION 1.0
                  DESCRIPTION "Compiler generation framework"
                  LANGUAGES CXX)

set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)

# version information
if(NOT DEFINED Deamer_VERSION_MAJOR)
  set(Deamer_VERSION_MAJOR 1)
endif()
if(NOT DEFINED Deamer_VERSION_MINOR)
  set(Deamer_VERSION_MINOR 0)
endif()
if(NOT DEFINED Deamer_VERSION_PATCH)
  set(Deamer_VERSION_PATCH 0)
endif()

add_subdirectory(lib)
add_custom_target(build_and_test ${CMAKE_CTEST_COMMAND} -V)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
	find_package(GTest)
	if (GTEST_FOUND)
		enable_testing()
		add_subdirectory(tests)
	else()
		enable_testing()
		include(GoogleTest)
		add_subdirectory(tests)
	endif()
endif()

install(DIRECTORY ${Deamer_SOURCE_DIR}/include/Deamer
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "LICENSE"
    )