cmake_minimum_required(VERSION 3.10)
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

project(NasNas)

# set compiler related settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set output files directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)

# find SFML
find_package(SFML COMPONENTS graphics audio)


# Select which optional modules to build
option(NASNAS_BUILD_RESLIB       "Build the RESLIB module"      ON)
option(NASNAS_BUILD_ECS          "Build the ECS module"         ON)
option(NASNAS_BUILD_TILEMAPPING  "Build the TILEMAPPING module" ON)
option(NASNAS_BUILD_UI           "Build the UI module"          ON)

option(NASNAS_BUILD_EXAMPLES  "Build the example applications" OFF)

include(cmake/NasNas.cmake)

# Static lib target
add_library(NasNas_static STATIC ${NasNas_Src} ${NasNas_Inc})
target_include_directories(NasNas_static PRIVATE include)
target_link_libraries(NasNas_static sfml-graphics sfml-audio)

# Shared lib target
add_library(NasNas_shared SHARED ${NasNas_Src} ${NasNas_Inc})
target_include_directories(NasNas_shared PRIVATE include)
target_link_libraries(NasNas_shared sfml-graphics sfml-audio)

if (NASNAS_BUILD_EXAMPLES)
    message("-- NasNas : Will build example applications")
    add_subdirectory(examples)
endif()
