file(GLOB_RECURSE SOURCE_LIST "${Deamer_SOURCE_DIR}/lib/*.cpp")
file(GLOB_RECURSE HEADER_LIST "${Deamer_SOURCE_DIR}/include/*.h")

add_library(Deamer STATIC ${HEADER_LIST})
target_sources(Deamer PRIVATE ${SOURCE_LIST})
target_include_directories(Deamer PUBLIC 
    $<BUILD_INTERFACE:${Deamer_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/>
)

target_compile_features(Deamer PUBLIC cxx_std_17)
set_target_properties(Deamer PROPERTIES LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON)

add_library(Deamer::Deamer ALIAS Deamer)

install(TARGETS Deamer
    EXPORT DeamerConfig
    DESTINATION lib/Deamer
    )

install(DIRECTORY ${Deamer_SOURCE_DIR}/include/Deamer
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "LICENSE"
    )

export(TARGETS
	Deamer
    NAMESPACE Deamer::
	FILE "${CMAKE_CURRENT_BINARY_DIR}/DeamerConfig.cmake"
)
install(EXPORT
	DeamerConfig
    NAMESPACE Deamer::
	DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Deamer"
)