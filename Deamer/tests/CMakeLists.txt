add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER Deamer/extern)
set_target_properties(gtest_main PROPERTIES FOLDER Deamer/extern)
set_target_properties(gmock PROPERTIES FOLDER Deamer/extern)
set_target_properties(gmock_main PROPERTIES FOLDER Deamer/extern)

macro(package_add_test TESTNAME)
    # create an exectuable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN})

    # link the Google test infrastructure, mocking library
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    target_link_libraries(${TESTNAME} Deamer)
	target_include_directories(${TESTNAME} PUBLIC ${Deamer_SOURCE_DIR}/include/ ${Deamer_SOURCE_DIR}/extern/googletest)

    gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
	
	add_dependencies(build_and_test ${TESTNAME})
	
	target_compile_features(${TESTNAME} PUBLIC cxx_std_17)
endmacro()

file(GLOB_RECURSE UNIT_TESTS *.cpp)
package_add_test(deamer_unit_tests ${UNIT_TESTS})