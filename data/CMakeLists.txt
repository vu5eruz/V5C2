# V5C2 — data/CMakeLists.txt

set(V5C2_DATA_DIRS
    "${V5C2_BUILD_OUTPUT_DIR}/images"
)

add_custom_command(
    OUTPUT ${V5C2_DATA_DIRS}
    
    COMMAND cmake -E make_directory "${V5C2_BUILD_OUTPUT_DIR}/images"
    COMMAND cmake -E copy_directory "data/images" "${V5C2_BUILD_OUTPUT_DIR}/images"

    DEPENDS "${CMAKE_SOURCE_DIR}/data/images/V5c2Icon.png"

    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

add_custom_target(v5c2_data ALL
    COMMENT "V5C2 Data Files"
    DEPENDS ${V5C2_DATA_DIRS}
)
