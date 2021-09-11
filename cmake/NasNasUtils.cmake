include(CMakePackageConfigHelpers)
include(FetchContent)
mark_as_advanced(FETCHCONTENT_BASE_DIR)

set(NasNas_Libs "")

define_property(GLOBAL
    PROPERTY NASNAS_ARCHIVE_TARGETS
    BRIEF_DOCS "Contains all available archive targets defined by NasNas"
    FULL_DOCS "Contains all available archive targets defined by NasNas"
)
define_property(GLOBAL
    PROPERTY NASNAS_LIBRARY_TARGETS
    BRIEF_DOCS "Contains all available library targets defined by NasNas"
    FULL_DOCS "Contains all available library targets defined by NasNas"
)
define_property(GLOBAL
    PROPERTY NASNAS_RUNTIME_TARGETS
    BRIEF_DOCS "Contains all available runtime targets defined by NasNas"
    FULL_DOCS "Contains all available runtime targets defined by NasNas"
)
define_property(GLOBAL
    PROPERTY NASNAS_EXECUTABLE_TARGETS
    BRIEF_DOCS "Contains all available executable targets defined by NasNas"
    FULL_DOCS "Contains all available executable targets defined by NasNas"
)

# Custom prints
macro(log_status string)
    message(STATUS "[NasNas] ${string}")
endmacro()

macro(log_fatal string)
    message(FATAL_ERROR "[NasNas] ${string}")
endmacro()

macro(log_list_item string)
    message(STATUS "          -> ${string}")
endmacro()

macro(log_targets type)
    get_property(targets_list GLOBAL PROPERTY NASNAS_${type}_TARGETS)
    if (targets_list)
        log_status("${type} targets available :")
        foreach(target ${targets_list})
            log_list_item("${target}")
        endforeach()
    endif()
endmacro()

# Downloads an external github repository as build dependency
function(download_dependency name git_url git_tag)
    string(TOLOWER ${name} name_lowercase)
    set(Deps_Source_Dir ${PROJECT_SOURCE_DIR}/_deps/${name})
    set(Deps_Build_Dir ${PROJECT_BINARY_DIR}/_deps/${name})
    set(Deps_SubBuild_Dir ${PROJECT_BINARY_DIR}/_deps/subbuilds/${name})

    if (EXISTS "${PROJECT_SOURCE_DIR}/_deps/${name}/CMakeLists.txt")
        add_subdirectory(${Deps_Source_Dir} ${Deps_Build_Dir})
        log_status("Found ${name} in ${PROJECT_SOURCE_DIR}/_deps/${name}")
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
    if (ANDROID)
        set(NASNAS_BUILD_SFML OFF)  # cannot build SFML as subproject for android
        set(SFML_DIR "${CMAKE_ANDROID_NDK}/sources/third_party/sfml/lib/${CMAKE_ANDROID_ARCH_ABI}/cmake/SFML/")
    endif()

    if (NOT NASNAS_BUILD_SFML)
        find_package(SFML 2 COMPONENTS graphics audio QUIET)
    endif()

    if (SFML_FOUND)
        log_status("Found SFML 2 in ${SFML_DIR}")
    elseif (ANDROID)
        log_fatal("Could not find SFML libraries in your Android NDK for the ${CMAKE_ANDROID_ARCH_ABI} architecture. Make sure you have built and installed SFML beforehand.")
    else()
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

    # update NasNas linked libraries
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

# Adds a target to the global NASNAS_${type}_TARGETS global property
function(NasNas_register_target name type)
    # append target to the global property matching the target type
    get_property(targets_list GLOBAL PROPERTY NASNAS_${type}_TARGETS)
    list(APPEND targets_list ${name})
    set_property(GLOBAL PROPERTY NASNAS_${type}_TARGETS ${targets_list})
endfunction()

# Creates library target for a NasNas module
function(NasNas_add_module_target name src inc)
    string(TOLOWER ${name} name_lowercase)
    set(target "NasNas-${name_lowercase}")

    set(type "STATIC")
    if (ANDROID)
        set(type "SHARED")
    endif()

    add_library(${target} ${type} ${src} ${inc})
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

    if (ANDROID)
        NasNas_register_target(${target} LIBRARY)
    else()
        NasNas_register_target(${target} ARCHIVE)
    endif()
endfunction()

# Creates executable for a NasNas example
function(NasNas_add_example_target name src inc)
    set(target ${name})

    add_executable(${target} "${src};${inc}")
    target_include_directories(${target} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
    target_include_directories(${target} PUBLIC $<INSTALL_INTERFACE:include>)
    target_link_libraries(${target} PRIVATE NasNas::Ecs NasNas::Reslib NasNas::Tilemapping NasNas::Tween NasNas::Ui)
    set_target_properties(
            ${target}
            PROPERTIES
            CXX_STANDARD 17
            DEBUG_POSTFIX -d
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin
    )

    NasNas_register_target(${target} EXECUTABLE)
endfunction()

# Creates export and install rules for all NasNas targets
function(NasNas_export_install targets)
    include(GNUInstallDirs)

    if (ANDROID)
        set(CMAKE_INSTALL_PREFIX "${CMAKE_ANDROID_NDK}/sources/third_party/nasnas" CACHE STRING "" FORCE)
        set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}/${CMAKE_ANDROID_ARCH_ABI}")
        set(CMAKE_INSTALL_BINDIR "${CMAKE_INSTALL_BINDIR}/${CMAKE_ANDROID_ARCH_ABI}")
    endif()

    # create build-tree export cmake module
    export(TARGETS ${targets} FILE ${PROJECT_BINARY_DIR}/NasNas.cmake NAMESPACE NasNas::)

    log_status("Install path : ${CMAKE_INSTALL_PREFIX}")

    # install headers
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/NasNas DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    if (NASNAS_EXAMPLES)
        # install examples assets
        install(DIRECTORY examples/assets DESTINATION ${CMAKE_INSTALL_BINDIR}/NasNas)
    endif()

    # install executables targets to NasNasTargets
    get_property(executable_targets_list GLOBAL PROPERTY NASNAS_EXECUTABLE_TARGETS)
    foreach(target ${executable_targets_list})
        install(TARGETS ${target} EXPORT NasNasTargets RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/NasNas)
    endforeach()

    # install runtime targets to NasNasTargets
    get_property(runtime_targets_list GLOBAL PROPERTY NASNAS_RUNTIME_TARGETS)
    foreach(target ${runtime_targets_list})
        install(TARGETS ${target} EXPORT NasNasTargets RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
    endforeach()

    # install archive targets to NasNasTargets
    get_property(archive_targets_list GLOBAL PROPERTY NASNAS_ARCHIVE_TARGETS)
    foreach(target ${archive_targets_list})
        install(TARGETS ${target} EXPORT NasNasTargets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    endforeach()

    # install library targets to NasNasTargets
    get_property(library_targets_list GLOBAL PROPERTY NASNAS_LIBRARY_TARGETS)
    foreach(target ${library_targets_list})
        install(TARGETS ${target} EXPORT NasNasTargets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    endforeach()

    # generate NasNasConfig.cmake
    configure_package_config_file(
            "${PROJECT_SOURCE_DIR}/cmake/NasNasConfig.cmake.in" "${PROJECT_BINARY_DIR}/NasNasConfig.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas
    )
    # install NasNasConfig.cmake file
    install(FILES ${PROJECT_BINARY_DIR}/NasNasConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas)
    # install NasNasTargets.cmake and NasNasTargets-${CMAKE_BUILD_TYPE}.cmake files
    install(EXPORT NasNasTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas NAMESPACE NasNas::)

    if (ANDROID)
        install(FILES ${PROJECT_SOURCE_DIR}/src/NasNas/Android.mk DESTINATION .)
    endif()
    # install license and readme
    install(FILES ${PROJECT_SOURCE_DIR}/LICENSE.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
    install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
endfunction()
