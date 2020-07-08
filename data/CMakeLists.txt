# V5C2 — data/CMakeLists.txt

set(V5C2_DATA_DIRS
    "${V5C2_BUILD_OUTPUT_DIR}/fonts"
    "${V5C2_BUILD_OUTPUT_DIR}/images"
)

file(GLOB V5C2_DATA_FILES
    "${CMAKE_SOURCE_DIR}/data/fonts/*"
    "${CMAKE_SOURCE_DIR}/data/images/*"
)

add_custom_command(
    OUTPUT ${V5C2_DATA_DIRS}

    COMMAND cmake -E make_directory "${V5C2_BUILD_OUTPUT_DIR}/fonts"
    COMMAND cmake -E copy_directory "data/fonts" "${V5C2_BUILD_OUTPUT_DIR}/fonts"
    
    COMMAND cmake -E make_directory "${V5C2_BUILD_OUTPUT_DIR}/images"
    COMMAND cmake -E copy_directory "data/images" "${V5C2_BUILD_OUTPUT_DIR}/images"

    DEPENDS ${V5C2_DATA_FILES}

    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

add_custom_target(v5c2_data ALL
    COMMENT "V5C2 Data Files"
    DEPENDS ${V5C2_DATA_DIRS}
)
