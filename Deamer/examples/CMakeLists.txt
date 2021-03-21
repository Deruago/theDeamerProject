add_custom_target(examples)

function(create_example EXAMPLE_NAME)
	set(EXAMPLE_TARGET_NAME ${EXAMPLE_NAME}_example)

	add_executable(${EXAMPLE_TARGET_NAME} ${ARGN})
	target_link_libraries(${EXAMPLE_TARGET_NAME} Deamer)
	target_include_directories(${EXAMPLE_TARGET_NAME} PRIVATE ${Deamer_SOURCE_DIR}/include/)

	add_dependencies(examples ${EXAMPLE_TARGET_NAME})
endfunction()

add_subdirectory(SimpleLang)
add_subdirectory(SimpleLang2)