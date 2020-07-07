# V5C2 — data/CMakeLists.txt

configure_file(
    "${CMAKE_SOURCE_DIR}/src/Main.h.in"
    "${CMAKE_BINARY_DIR}/src/Main.h"
)

add_executable(v5c2
    "Background.cpp"
    "Engine.cpp"
    "Main.cpp"
    "State.cpp"
)

add_dependencies(v5c2 v5c2_data)

set_target_properties(v5c2 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    ARCHIVE_OUTPUT_DIRECTORY "${V5C2_BUILD_OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${V5C2_BUILD_OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${V5C2_BUILD_OUTPUT_DIR}"
    OUTPUT_NAME "v5c2"
    WIN32_EXECUTABLE TRUE
)

target_compile_options(v5c2 PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -Wpedantic >
)

target_include_directories(v5c2 PUBLIC
    "${CMAKE_SOURCE_DIR}/external/stb"
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_BINARY_DIR}/src"
)

target_link_libraries(v5c2 PUBLIC
    glad
    glfw
)
