cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(Deamer VERSION 2.3.0
                  DESCRIPTION "Infrastructure for compiler and ecosystem generation."
                  LANGUAGES CXX)

set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (default Debug)" FORCE)
endif()

# version information
if(NOT DEFINED Deamer_VERSION_MAJOR)
  set(Deamer_VERSION_MAJOR 2)
endif()
if(NOT DEFINED Deamer_VERSION_MINOR)
  set(Deamer_VERSION_MINOR 3)
endif()
if(NOT DEFINED Deamer_VERSION_PATCH)
  set(Deamer_VERSION_PATCH 0)
endif()

add_subdirectory(lib)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	option(DEAMER_BUILD_EXAMPLES "Build the examples" OFF)
	option(DEAMER_BUILD_TESTS "Build the tests" ON)

	find_package(Doxygen)
	if(Doxygen_FOUND)
		add_subdirectory(docs)
	else()
		message(STATUS "Doxygen not found, not building docs")
	endif()

	if(DEAMER_BUILD_EXAMPLES)
		message(STATUS "Examples can now be build")
		add_subdirectory(examples)
	endif()

	if(DEAMER_BUILD_TESTS)
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
endif()