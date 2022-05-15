file(GLOB_RECURSE SOURCE_LIST "${Deamer_SOURCE_DIR}/lib/*.cpp")
file(GLOB_RECURSE HEADER_LIST "${Deamer_SOURCE_DIR}/include/*.h")

add_library(Deamer STATIC ${HEADER_LIST})
target_sources(Deamer PRIVATE ${SOURCE_LIST})
target_include_directories(Deamer PUBLIC 
    $<BUILD_INTERFACE:${Deamer_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(Deamer PRIVATE Deamer::dregx)

target_compile_features(Deamer PUBLIC cxx_std_17)
set_target_properties(Deamer PROPERTIES LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON)

add_library(Deamer::Deamer ALIAS Deamer)

# Install Targets

install(TARGETS Deamer
    EXPORT Deamer_Exports
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/Deamer"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/Deamer"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/Deamer"
    )

export(TARGETS
	Deamer
    NAMESPACE Deamer::
	FILE "${CMAKE_CURRENT_BINARY_DIR}/Deamer_Exports.cmake"
)

install(EXPORT
	Deamer_Exports
    NAMESPACE Deamer::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Deamer"
)

# Install Headers

install(DIRECTORY ${Deamer_SOURCE_DIR}/include/Deamer
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "LICENSE"
    )