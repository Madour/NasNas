cmake_minimum_required(VERSION 3.10)
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

project(NasNas)

# SFML static libs option
set(BUILD_SHARED_LIBS FALSE)
set(SFML_USE_STATIC_STD_LIBS TRUE)
mark_as_advanced(BUILD_SHARED_LIBS)
mark_as_advanced(SFML_USE_STATIC_STD_LIBS)
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

## NasNas options
# Select optional modules
option(NASNAS_BUILD_RESLIB      "Build the RESLIB module"           ON)
option(NASNAS_BUILD_ECS         "Build the ECS module"              ON)
option(NASNAS_BUILD_TILEMAPPING "Build the TILEMAPPING module"      ON)
option(NASNAS_BUILD_UI          "Build the UI module"               ON)
# Select optional targets
option(NASNAS_EXAMPLES          "Build the example applications"    OFF)

include(cmake/NasNas.cmake)

# Static lib target
set(NASNAS_TGT_STATIC "NasNas")
add_library(${NASNAS_TGT_STATIC} STATIC ${NasNas_Src} ${NasNas_Inc})
target_include_directories(${NASNAS_TGT_STATIC} PRIVATE include)
target_link_libraries(${NASNAS_TGT_STATIC} sfml-graphics sfml-audio)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message(STATUS "GNU or Clang detected")
  target_link_libraries(${NASNAS_TGT_STATIC} m stdc++fs stdc++)
endif()

set_target_properties(
        ${NASNAS_TGT_STATIC}
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        DEBUG_POSTFIX -d
        RUNTIME_OUTPUT_DIRECTORY bin
        RUNTIME_OUTPUT_DIRECTORY_DEBUG bin
        RUNTIME_OUTPUT_DIRECTORY_RELEASE bin
        ARCHIVE_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG lib
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE lib
        LIBRARY_OUTPUT_DIRECTORY lib
        LIBRARY_OUTPUT_DIRECTORY_DEBUG lib
        LIBRARY_OUTPUT_DIRECTORY_RELEASE lib
)

# Examples target
set(NASNAS_TGT_EXAMPLES "")
if (NASNAS_EXAMPLES)
    set(NASNAS_TGT_EXAMPLES "NasNas_examples")
endif()

if (NASNAS_EXAMPLES)
    add_subdirectory(examples)
endif()

message(STATUS "NasNas : Targets available to build : ${NASNAS_TGT_STATIC} ${NASNAS_TGT_EXAMPLES}")
