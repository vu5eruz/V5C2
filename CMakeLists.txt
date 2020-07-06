# V5C2 — top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()


project(
    V5C2
    VERSION 0.3.0
    DESCRIPTION "vu5eruz's chess for two"
    LANGUAGES CXX
)


if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(V5C2_DEBUG 1)
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(V5C2_PLATFORM_WINDOWS 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(V5C2_PLATFORM_UNIX 1)
    set(V5C2_PLATFORM_LINUX 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" AND NOT IOS)
    set(V5C2_PLATFORM_UNIX 1)
    set(V5C2_PLATFORM_MACOSX 1)
else()
    message(FATAL_ERROR "Unsupported operating system or environment")
endif()


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)


set(V5C2_BUILD_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/V5C2")

add_subdirectory(data)
add_subdirectory(src)
