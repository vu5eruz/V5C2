# TODO(vu5eruz): Improve this

add_custom_target(v5c2_data ALL COMMENT "V5C2 Data Files")

add_custom_command(
    TARGET v5c2_data PRE_BUILD

    COMMAND cmake -E make_directory "${V5C2_BUILD_OUTPUT_DIR}/images"
    COMMAND cmake -E copy_directory "data/images" "${V5C2_BUILD_OUTPUT_DIR}/images"

    COMMAND cmake -E make_directory "${V5C2_BUILD_OUTPUT_DIR}/fonts"
    COMMAND cmake -E copy_directory "data/fonts" "${V5C2_BUILD_OUTPUT_DIR}/fonts"

    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
