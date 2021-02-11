cmake_minimum_required(VERSION 3.10)
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

project(NasNas)

include(cmake/Macros.cmake)

check_compiler()

## NasNas options
# Select optional modules
option(NASNAS_BUILD_RESLIB      "Build the RESLIB module"               ON)
option(NASNAS_BUILD_ECS         "Build the ECS module"                  ON)
option(NASNAS_BUILD_TILEMAPPING "Build the TILEMAPPING module"          ON)
option(NASNAS_BUILD_UI          "Build the UI module"                   ON)
# Select optional targets
option(NASNAS_EXAMPLES          "Build the example applications"        OFF)
option(NASNAS_FIND_SFML         "Find an existing installation of SFML" ON)

# find SFML install location or SFML source files and dependencies
find_SFML()

# find NasNas source files and dependencies
find_NasNas()

# NasNas static lib target
set(NASNAS_TGT_STATIC "NasNas")
add_library(${NASNAS_TGT_STATIC} STATIC ${NasNas_Src} ${NasNas_Inc})

target_include_directories(${NASNAS_TGT_STATIC} PRIVATE include)
target_link_libraries(${NASNAS_TGT_STATIC} ${NasNas_Libs})

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
    add_subdirectory(examples)
endif()

message(STATUS "NasNas : Targets available to build : ${NASNAS_TGT_STATIC} ${NASNAS_TGT_EXAMPLES}")
