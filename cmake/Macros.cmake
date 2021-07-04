
macro(find_SFML)
    if(NASNAS_FIND_SFML)
        find_package(SFML 2 COMPONENTS graphics audio QUIET)
    endif()

    if (SFML_FOUND)
        message(STATUS "Found SFML in ${SFML_DIR}")
    else ()
        set(BUILD_SHARED_LIBS FALSE)
        set(SFML_USE_STATIC_STD_LIBS FALSE)
        mark_as_advanced(BUILD_SHARED_LIBS)
        add_subdirectory(SFML)

        if(MSVC AND SFML_USE_STATIC_STD_LIBS)
            foreach(flag
                    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
                if(${flag} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
                endif()
            endforeach()
        endif()
        message(STATUS "Found SFML 2.5.1 in ${CMAKE_CURRENT_SOURCE_DIR}/SFML")
    endif()
    set(NasNas_Libs "${NasNas_Libs};sfml-graphics;sfml-audio")
endmacro()

macro(check_compiler)
    if(NOT WIN32)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set(${NasNas_Libs} "${NasNas_Libs};m;stdc++fs;stdc++")
        endif()
    endif()
endmacro()

function(NasNas_add_module name src inc)
    message("   -> ${name}")

    set(target "NasNas-${name}")

    add_library(${target} STATIC ${src} ${inc})
    target_include_directories(${target} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
    target_link_libraries(${target} ${NasNas_Libs})

    set_target_properties(
            ${target}
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS ON
            DEBUG_POSTFIX -d
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
            ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib
            ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
            LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib
            LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib
    )

    # update global list of targets
    get_property(NasNas_Targets GLOBAL PROPERTY NASNAS_TARGETS)
    list(APPEND NasNas_Targets ${target})
    set_property(GLOBAL PROPERTY NASNAS_TARGETS ${NasNas_Targets})
endfunction()
