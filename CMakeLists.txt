cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()

project(
	V5C2
	VERSION 0.1.0
	DESCRIPTION "vu5eruz's chess for two"
	LANGUAGES CXX
)

add_subdirectory(src)
