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

# loop on all the examples directories and create a target for each
subdirectories(NasNas_Examples ${CMAKE_CURRENT_LIST_DIR})
foreach(example ${NasNas_Examples})
    file(GLOB_RECURSE SRC ${example}/*.cpp)
    file(GLOB_RECURSE INC ${example}/*.hpp)

    NasNas_add_example(${example} "${SRC}" "${INC}")
    add_dependencies(NasNas_examples ${example})
endforeach()

install(DIRECTORY assets DESTINATION ${CMAKE_INSTALL_BINDIR}/NasNas)

