cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(Deamer VERSION 2.3.0
                  DESCRIPTION "Infrastructure for compiler and ecosystem generation."
                  LANGUAGES CXX)

include(GNUInstallDirs)

find_package(dregx REQUIRED)

set(CMAKE_BUILD_WITH_INSTALL_NAME_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (default Debug)" FORCE)
endif()

add_subdirectory(lib)

macro(option_enable OPTION_NAME OPTION_TEXT OPTION_DEFAULT)
	if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
		option(${OPTION_NAME} ${OPTION_TEXT} ${OPTION_DEFAULT})
	else()
		option(${OPTION_NAME} ${OPTION_TEXT} OFF)
	endif()
endmacro()

option_enable(DEAMER_DEBUG "Debug Build" OFF)

if (DEAMER_DEBUG)

else()
	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		set_target_properties(Deamer PROPERTIES COMPILE_FLAGS "-O3")
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set_target_properties(Deamer PROPERTIES COMPILE_FLAGS "-O3")
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		set_target_properties(Deamer PROPERTIES COMPILE_FLAGS "/O3")
	endif()
endif()

option_enable(DEAMER_ENABLE_DOXYGEN "Build the examples" ON)
option_enable(DEAMER_BUILD_EXAMPLES "Build the examples" OFF)
option_enable(DEAMER_BUILD_TESTS "Build the tests" ON)

if(DEAMER_ENABLE_DOXYGEN)
	find_package(Doxygen)
	if(Doxygen_FOUND)
		add_subdirectory(docs)
	else()
		message(STATUS "Doxygen not found, not building docs")
	endif()
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

# Package

include(CMakePackageConfigHelpers)

configure_package_config_file(${Deamer_SOURCE_DIR}/cmake/DeamerConfig.cmake.in
  "${Deamer_BINARY_DIR}/DeamerConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Deamer
)

write_basic_package_version_file(
	"DeamerConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES
	${Deamer_BINARY_DIR}/DeamerConfig.cmake
	${Deamer_BINARY_DIR}/DeamerConfigVersion.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Deamer
)