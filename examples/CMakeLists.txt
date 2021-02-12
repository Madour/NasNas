macro(subdirectories result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child} AND NOT ${child} MATCHES assets)
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

add_custom_target(NasNas_examples)

# loop on all the examples directories and create a target for each
subdirectories(examples ${CMAKE_CURRENT_LIST_DIR})
foreach(example ${examples})
    file(GLOB_RECURSE Src ${example}/*.cpp)
    file(GLOB_RECURSE Inc ${example}/*.hpp)

    add_executable(${example} "${Src};${Inc}")
    target_include_directories(${example} PRIVATE ../include)
    target_link_libraries(${example} PRIVATE NasNas)
    set_target_properties(
            ${example}
            PROPERTIES
            CXX_STANDARD 17
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin
    )

    add_dependencies(NasNas_examples ${example})
endforeach()

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
