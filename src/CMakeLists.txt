if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(V5C2_DEBUG 1)
endif()

if(UNIX AND NOT APPLE)
    set(V5C2_PLATFORM_LINUX 1)
elseif(UNIX AND APPLE)
    set(V5C2_PLATFORM_APPLE 1)
elseif(WIN32)
    set(V5C2_PLATFORM_WINDOWS 1)
endif()

configure_file(
    "${CMAKE_SOURCE_DIR}/src/main.h.in"
    "${CMAKE_BINARY_DIR}/src/main.h"
)

add_executable(v5c2 WIN32
	"main.cpp"
)

set_target_properties(v5c2 PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    OUTPUT_NAME "v5c2"
)

target_compile_definitions(v5c2 PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>: UNICODE=1 _UNICODE=1 >
)

target_compile_options(v5c2 PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -Wpedantic >
)

target_include_directories(v5c2 PUBLIC
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_BINARY_DIR}/src"
)

