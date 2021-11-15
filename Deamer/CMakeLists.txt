cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(Deamer VERSION 2.1.1
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
  set(Deamer_VERSION_MINOR 1)
endif()
if(NOT DEFINED Deamer_VERSION_PATCH)
  set(Deamer_VERSION_PATCH 1)
endif()

add_subdirectory(lib)
add_custom_target(build_and_test ${CMAKE_CTEST_COMMAND} -V)

find_package(Doxygen)
if(Doxygen_FOUND)
	add_subdirectory(docs)
else()
	message(STATUS "Doxygen not found, not building docs")
endif()


option(EXAMPLES "Build the examples" OFF)
if(EXAMPLES)
	message(STATUS "Examples can now be build")
	add_subdirectory(examples)
endif()

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

export(TARGETS
	Deamer
	FILE "${CMAKE_CURRENT_BINARY_DIR}/DeamerConfig.cmake"
)

install(EXPORT
	DeamerConfig
	DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Deamer"
)