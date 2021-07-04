macro(subdirectories result current_dir)
    file(GLOB children RELATIVE ${current_dir} ${current_dir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${current_dir}/${child} AND NOT ${child} MATCHES assets)
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()


add_custom_target(NasNas_examples)
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

get_property(NasNas_Targets GLOBAL PROPERTY NASNAS_TARGETS)
list(APPEND NasNas_Targets NasNas_examples)

# loop on all the examples directories and create a target for each
subdirectories(NasNas_Examples ${CMAKE_CURRENT_LIST_DIR})
foreach(example ${NasNas_Examples})
    file(GLOB_RECURSE SRC ${example}/*.cpp)
    file(GLOB_RECURSE INC ${example}/*.hpp)

    add_executable(${example} "${SRC};${INC}")
    target_include_directories(${example} PUBLIC ../include)
    target_link_libraries(${example} PRIVATE NasNas)
    set_target_properties(
            ${example}
            PROPERTIES
            CXX_STANDARD 17
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin
    )

    list(APPEND NasNas_Targets ${example})
    add_dependencies(NasNas_examples ${example})
endforeach()

set_property(GLOBAL PROPERTY NASNAS_TARGETS ${NasNas_Targets})
