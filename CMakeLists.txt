cmake_minimum_required(VERSION 3.10)
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

project(NasNas)

# find SFML
find_package(SFML COMPONENTS graphics audio)


# Select optional modules
option(NASNAS_BUILD_RESLIB      "Build the RESLIB module"           ON)
option(NASNAS_BUILD_ECS         "Build the ECS module"              ON)
option(NASNAS_BUILD_TILEMAPPING "Build the TILEMAPPING module"      ON)
option(NASNAS_BUILD_UI          "Build the UI module"               ON)

# Select optional targets
option(NASNAS_EXAMPLES          "Build the example applications"    OFF)
option(NASNAS_SHARED            "Build the shared library"          OFF)


include(cmake/NasNas.cmake)


# Static lib target
set(NASNAS_TGT_STATIC "NasNas_static")
add_library(${NASNAS_TGT_STATIC} STATIC ${NasNas_Src} ${NasNas_Inc})
target_include_directories(${NASNAS_TGT_STATIC} PRIVATE include)
target_link_libraries(${NASNAS_TGT_STATIC} sfml-graphics sfml-audio)


# Shared lib target
set(NASNAS_TGT_SHARED "")
if (NASNAS_SHARED)
    set(NASNAS_TGT_SHARED "NasNas_shared")
    add_library(${NASNAS_TGT_SHARED} SHARED ${NasNas_Src} ${NasNas_Inc})
    target_include_directories(${NASNAS_TGT_SHARED} PRIVATE include)
    target_link_libraries(${NASNAS_TGT_SHARED} sfml-graphics sfml-audio)
endif()


# Examples target
set(NASNAS_TGT_EXAMPLES "")
if (NASNAS_BUILD_EXAMPLES)
    set(NASNAS_TGT_EXAMPLES "NasNas_examples")
endif()

set_target_properties(
    ${NASNAS_TGT_STATIC} ${NASNAS_TGT_SHARED}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY bin
    ARCHIVE_OUTPUT_DIRECTORY lib
    LIBRARY_OUTPUT_DIRECTORY lib
)

if (NASNAS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

message(STATUS "NasNas : Targets available to build : ${NASNAS_TGT_STATIC} ${NASNAS_TGT_SHARED} ${NASNAS_TGT_EXAMPLES}")
