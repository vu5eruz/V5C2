# V5C2 — data/CMakeLists.txt

add_custom_target(v5c2_data ALL COMMENT "V5C2 Data Files")

add_custom_command(
    TARGET v5c2_data PRE_BUILD

    COMMAND cmake -E make_directory "${V5C2_BUILD_OUTPUT_DIR}/images"
    COMMAND cmake -E copy_directory "data/images" "${V5C2_BUILD_OUTPUT_DIR}/images"

    DEPENDS "${CMAKE_SOURCE_DIR}/data/images/V5c2Icon.png"

    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
