include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(FetchContent)

set(NasNas_Libs "")

# global list that contains all NasNas targets
define_property(GLOBAL
    PROPERTY NASNAS_TARGETS
    BRIEF_DOCS "Contains all available targets defined by NasNas"
    FULL_DOCS "Contains all available targets defined by NasNas"
)

# Custom prints
macro(log_status string)
    message(STATUS "[NasNas] ${string}")
endmacro()

macro(log_list_item string)
    message(STATUS "          -> ${string}")
endmacro()

# Downloads an external github repository as build dependency
function(download_dependency name git_url git_tag)
    string(TOLOWER ${name} name_lowercase)
    set(Deps_Source_Dir ${PROJECT_SOURCE_DIR}/_deps/${name})
    set(Deps_Build_Dir ${PROJECT_BINARY_DIR}/_deps/${name})
    set(Deps_SubBuild_Dir ${PROJECT_BINARY_DIR}/_deps/subbuilds/${name})

    if (EXISTS "${PROJECT_SOURCE_DIR}/_deps/${name}/CMakeLists.txt")
        add_subdirectory(${Deps_Source_Dir} ${Deps_Build_Dir})
        log_status("Found SFML in ${PROJECT_SOURCE_DIR}/_deps/${name}")
    else()
        log_status("Downloading ${name} in ${Deps_Source_Dir}... (this can take some time)")
        FetchContent_Declare(
                ${name}
                GIT_REPOSITORY ${git_url}
                GIT_TAG ${git_tag}
                SOURCE_DIR ${Deps_Source_Dir}
                BINARY_DIR ${Deps_Build_Dir}
                SUBBUILD_DIR ${Deps_SubBuild_Dir}
        )
        FetchContent_MakeAvailable(${name})
        log_status("${name} downloaded in ${${name}_SOURCE_DIR}")
    endif()
endfunction()

# Looks for an installed SFML package. If not found, downloads it as a dependency
macro(find_SFML)
    if(NOT NASNAS_BUILD_SFML)
        find_package(SFML 2 COMPONENTS graphics audio QUIET)
    endif()

    if (SFML_FOUND)
        log_status("Found SFML 2 in ${SFML_DIR}")
    else ()
        set(NASNAS_BUILD_SFML ON)
        set(BUILD_SHARED_LIBS FALSE)
        set(SFML_USE_STATIC_STD_LIBS FALSE)
        mark_as_advanced(BUILD_SHARED_LIBS)

        download_dependency(SFML "https://github.com/SFML/SFML" "089f0fd8b4fb025bfb2f118c51333c77855e9413")

        if(MSVC AND SFML_USE_STATIC_STD_LIBS)
            foreach(flag
                    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
                if(${flag} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
                endif()
            endforeach()
        endif()
    endif()
    set(NasNas_Libs "${NasNas_Libs};sfml-graphics;sfml-audio")
endmacro()

# Checks if compiler is Clang or Gcc and link needed libraries
macro(check_compiler)
    if(NOT WIN32)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set(${NasNas_Libs} "${NasNas_Libs};m;stdc++fs;stdc++")
        endif()
    endif()
endmacro()

# Adds a target to the global NASNAS_TARGETS list and exports it
function(NasNas_register_target name type)
    # append target to the global NasNas_Targets list
    get_property(NasNas_Targets GLOBAL PROPERTY NASNAS_TARGETS)
    list(APPEND NasNas_Targets ${name})
    set_property(GLOBAL PROPERTY NASNAS_TARGETS ${NasNas_Targets})

    # export target to NasNasTargets
    if (${type} MATCHES ARCHIVE)
        install(TARGETS ${name} EXPORT NasNasTargets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    elseif(${type} MATCHES RUNTIME)
        install(TARGETS ${name} EXPORT NasNasTargets RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/NasNas)
    endif()
endfunction()

# Creates STATIC library target for a NasNas module
function(NasNas_add_module_target name src inc)
    string(TOLOWER ${name} name_lowercase)
    set(target "NasNas-${name_lowercase}")

    add_library(${target} STATIC ${src} ${inc})
    add_library(NasNas::${name} ALIAS ${target})
    target_include_directories(${target} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
    target_include_directories(${target} PUBLIC $<INSTALL_INTERFACE:include>)
    target_link_libraries(${target} ${NasNas_Libs})
    if (NOT ${target} MATCHES core)
        target_link_libraries(${target} NasNas-core)
    endif()

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
            EXPORT_NAME ${name}
    )

    NasNas_register_target(${target} ARCHIVE)
endfunction()

# Creates executable for a NasNas example
function(NasNas_add_example_target name src inc)
    set(target ${name})

    add_executable(${target} "${src};${inc}")
    target_include_directories(${target} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
    target_include_directories(${target} PUBLIC $<INSTALL_INTERFACE:include>)
    target_link_libraries(${target} PRIVATE NasNas::Ecs NasNas::Reslib NasNas::Tilemapping NasNas::Ui)
    set_target_properties(
            ${target}
            PROPERTIES
            CXX_STANDARD 17
            DEBUG_POSTFIX -d
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin
    )

    NasNas_register_target(${target} RUNTIME)
endfunction()

# Creates export and install rules for all NasNas targets
function(NasNas_export_install targets)
    # create build-tree export
    export(TARGETS ${targets} FILE ${PROJECT_BINARY_DIR}/NasNas.cmake NAMESPACE NasNas::)

    # install license and readme
    install(FILES ${PROJECT_SOURCE_DIR}/LICENSE.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
    install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
    # install headers
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/NasNas DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    # install exported targets
    install(EXPORT NasNasTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas NAMESPACE NasNas::)

    # generate NasNasConfig.cmake
    configure_package_config_file(
            "${PROJECT_SOURCE_DIR}/cmake/NasNasConfig.cmake.in" "${PROJECT_BINARY_DIR}/NasNasConfig.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas
    )
    # install NasNasConfig.cmake file
    install(FILES ${PROJECT_BINARY_DIR}/NasNasConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas)
endfunction()
