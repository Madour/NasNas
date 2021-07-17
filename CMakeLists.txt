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

# NasNas modules names
set(NASNAS_OPTIONAL_MODULES "RESLIB;ECS;TILEMAPPING;UI")
set(NASNAS_MODULES "CORE;${NASNAS_OPTIONAL_MODULES}")

# Select optional modules
foreach(module ${NASNAS_OPTIONAL_MODULES})
    option(NASNAS_BUILD_${module} "Build the ${module} module" ON)
endforeach()

# Select optional targets
option(NASNAS_EXAMPLES          "Build the example applications"        OFF)
option(NASNAS_FIND_SFML         "Find an existing installation of SFML" ON)

include(cmake/NasNasUtils.cmake)

check_compiler()

# find SFML or download it if not found
find_SFML()

# add NasNas subdirectory
add_subdirectory(${PROJECT_SOURCE_DIR}/src/NasNas)

if (NASNAS_EXAMPLES)
    # add examples subdirectory
    add_subdirectory(examples)
endif()

# print available targets
get_property(NasNas_Targets GLOBAL PROPERTY NASNAS_TARGETS)

log_status("Targets available to build :")
foreach(target ${NasNas_Targets})
    log_list_item("${target}")
endforeach()
if (NASNAS_EXAMPLES)
    log_list_item("NasNas_examples")
endif()

# export and install targets
NasNas_export_install("${NasNas_Targets}")
