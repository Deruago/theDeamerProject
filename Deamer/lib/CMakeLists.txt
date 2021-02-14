file(GLOB_RECURSE HEADER_LIST "${Deamer_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SOURCE_LIST "${Deamer_SOURCE_DIR}/lib/*.cpp")

add_library(Deamer STATIC ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(Deamer PRIVATE ../include)

target_compile_features(Deamer PRIVATE cxx_std_17)

install(TARGETS Deamer
    DESTINATION lib/Deamer
    )