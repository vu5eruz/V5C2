cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()


project(
    V5C2
    VERSION 0.2.0
    DESCRIPTION "vu5eruz's chess for two"
    LANGUAGES CXX
)


if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(V5C2_DEBUG 1)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(V5C2_PLATFORM_WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(V5C2_PLATFORM_UNIX 1)
    if(ANDROID)
        set(V5C2_PLATFORM_ANDROID 1)
    else()
        set(V5C2_PLATFORM_LINUX 1)
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "^k?FreeBSD$")
    set(V5C2_PLATFORM_UNIX 1)
    set(V5C2_PLATFORM_FREEBSD 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^OpenBSD$")
    set(V5C2_PLATFORM_UNIX 1)
    set(V5C2_PLATFORM_OPENBSD 1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    if(IOS)
        # XXX: Is iOS an Unix-like?
        set(V5C2_PLATFORM_IOS 1)
    else()
        set(V5C2_PLATFORM_UNIX 1)
        set(V5C2_PLATFORM_MACOSX 1)
    endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    set(V5C2_PLATFORM_UNIX 1)
    set(V5C2_PLATFORM_ANDROID 1)
else()
    message(FATAL_ERROR "Unsupported operating system or environment")
endif()


set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

add_subdirectory(external/SFML)


set(V5C2_BUILD_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/V5C2")

add_subdirectory(data)
add_subdirectory(src)
