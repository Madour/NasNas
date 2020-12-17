macro(add_example_target target)
    cmake_parse_arguments(EX "" "RES_DIR" "SRC" ${ARGN})

    add_executable( ${target} ${EX_SRC} )
    target_include_directories(${target} PRIVATE ../../include)
    target_link_libraries(${target} PRIVATE NasNas sfml-graphics sfml-audio )
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${target} PROPERTY RUNTIME_OUTPUT_DIRECTORY bin)

    if (EX_RES_DIR)
        get_target_property(BIN_DIR ${target} RUNTIME_OUTPUT_DIRECTORY)
        file(COPY ${EX_RES_DIR} DESTINATION ${BIN_DIR})
    endif()

    add_dependencies(NasNas_examples ${target})
endmacro()

add_custom_target(NasNas_examples)

add_subdirectory(demo)
add_subdirectory(split_view)
