cmake_minimum_required(VERSION 3.10)
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

project(
    NasNas
    VERSION 0.1.0
    DESCRIPTION "An intuitive and beginner friendly 2D game framework"
    LANGUAGES CXX
    HOMEPAGE_URL "https://github.com/Madour/NasNas"
)

## NasNas options
# Select optional modules
option(NASNAS_BUILD_RESLIB      "Build the RESLIB module"               ON)
option(NASNAS_BUILD_ECS         "Build the ECS module"                  ON)
option(NASNAS_BUILD_TILEMAPPING "Build the TILEMAPPING module"          ON)
option(NASNAS_BUILD_UI          "Build the UI module"                   ON)
# Select optional targets
option(NASNAS_EXAMPLES          "Build the example applications"        OFF)
option(NASNAS_FIND_SFML         "Find an existing installation of SFML" ON)

include(cmake/NasNasUtils.cmake)

check_compiler()

# find SFML install location or SFML source files and dependencies
find_SFML()

# add NasNas subdirectory
add_subdirectory(${PROJECT_SOURCE_DIR}/src/NasNas)

if (NASNAS_EXAMPLES)
    # add examples subdirectory
    add_subdirectory(examples)
endif()

# print available targets
get_property(NasNas_Targets GLOBAL PROPERTY NASNAS_TARGETS)

message(STATUS "NasNas : Targets available to build :")
foreach(target ${NasNas_Targets})
    message("   -> ${target}")
endforeach()
if (NASNAS_EXAMPLES)
    message("   -> NasNas_examples")
endif()

# export and install targets
NasNas_export_install()
