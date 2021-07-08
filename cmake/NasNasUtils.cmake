include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(NasNas_Libs "")

# global list that contains all NasNas targets
define_property(GLOBAL
    PROPERTY NASNAS_TARGETS
    BRIEF_DOCS "Contains all available targets defined by NasNas"
    FULL_DOCS "Contains all available targets defined by NasNas"
)

macro(find_SFML)
    if(NASNAS_FIND_SFML)
        find_package(SFML 2 COMPONENTS graphics audio QUIET)
    endif()

    if (SFML_FOUND)
        message(STATUS "Found SFML 2 in ${SFML_DIR}")
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

function(NasNas_register_target name)
    get_property(NasNas_Targets GLOBAL PROPERTY NASNAS_TARGETS)
    list(APPEND NasNas_Targets ${name})
    set_property(GLOBAL PROPERTY NASNAS_TARGETS ${NasNas_Targets})
endfunction()

function(NasNas_add_module name src inc)
    message("   -> ${name}")

    string(TOLOWER ${name} name_lowercase)
    set(target "NasNas-${name_lowercase}")

    add_library(${target} STATIC ${src} ${inc})
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

    add_library(NasNas::${name} ALIAS ${target})

    install(TARGETS ${target} EXPORT NasNasTargets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

    NasNas_register_target(${target})
endfunction()

function(NasNas_add_example name src inc)
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

    install(TARGETS ${target} EXPORT NasNasTargets RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/NasNas)

    NasNas_register_target(${target})
endfunction()

function(NasNas_export_install)
    # build tree export
    export(TARGETS ${NasNas_Targets} FILE ${PROJECT_BINARY_DIR}/NasNas.cmake NAMESPACE NasNas::)

    # generate NasNasConfig.cmake
    configure_package_config_file(
            "${PROJECT_SOURCE_DIR}/cmake/NasNasConfig.cmake.in" "${PROJECT_BINARY_DIR}/NasNasConfig.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas
    )
    # install NasNasConfig.cmake file
    install(FILES ${PROJECT_BINARY_DIR}/NasNasConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas)
    # install license and readme
    install(FILES ${PROJECT_SOURCE_DIR}/LICENSE.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
    install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
    # install headers
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/NasNas DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    # install exported targets
    install(EXPORT NasNasTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas NAMESPACE NasNas::)
endfunction()
