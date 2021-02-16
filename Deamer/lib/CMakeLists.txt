file(GLOB_RECURSE HEADER_LIST "${Deamer_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCE_LIST "${Deamer_SOURCE_DIR}/lib/*.cpp")

add_library(Deamer STATIC ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(Deamer PRIVATE ../include)
target_compile_features(Deamer PRIVATE cxx_std_17)
set_target_properties(Deamer PROPERTIES LINKER_LANGUAGE CXX)

add_library(Deamer_Shared SHARED ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(Deamer_Shared PRIVATE ../include)
target_compile_features(Deamer_Shared PUBLIC cxx_std_17)
set_target_properties(Deamer_Shared PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS Deamer
    DESTINATION lib/Deamer
    )