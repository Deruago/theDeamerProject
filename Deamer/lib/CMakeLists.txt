file(GLOB_RECURSE SOURCE_LIST "${Deamer_SOURCE_DIR}/lib/*.cpp")
file(GLOB_RECURSE HEADER_LIST "${Deamer_SOURCE_DIR}/include/*.h")

add_library(Deamer STATIC ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(Deamer PUBLIC 
    $<BUILD_INTERFACE:${Deamer_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/>
)

target_compile_features(Deamer PUBLIC cxx_std_17)
set_target_properties(Deamer PROPERTIES LINKER_LANGUAGE CXX POSITION_INDEPENDENT_CODE ON)

if(DEAMER_CREATE_SHARED_LIB)
    add_library(Deamer_Shared SHARED ${SOURCE_LIST} ${HEADER_LIST})
    target_link_libraries(Deamer_Shared PUBLIC DREGX)

    target_include_directories(Deamer_Shared PUBLIC 
        $<BUILD_INTERFACE:${Deamer_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/>
    )

    target_compile_features(Deamer_Shared PUBLIC cxx_std_17)
    set_target_properties(Deamer_Shared PROPERTIES LINKER_LANGUAGE CXX)
endif()

install(TARGETS Deamer
    EXPORT DeamerConfig
    DESTINATION lib/Deamer
    )