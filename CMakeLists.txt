cmake_minimum_required(VERSION 3.10)
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW) # Enable CMake search paths defined by NasNas_ROOT variable
endif()
if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW) # NasNas options will not override user defined variable if they exist
endif()

project(
    NasNas
    VERSION 0.2.0
    DESCRIPTION "An intuitive and beginner friendly 2D game framework"
    LANGUAGES CXX
    HOMEPAGE_URL "https://github.com/Madour/NasNas"
)

# NasNas modules names
set(NASNAS_OPTIONAL_MODULES "ECS;RESLIB;TILEMAPPING;TWEEN;UI")
set(NASNAS_MODULES "CORE;${NASNAS_OPTIONAL_MODULES}")

# Select optional modules
foreach(module ${NASNAS_OPTIONAL_MODULES})
    option(NASNAS_BUILD_${module} "Build the ${module} module" ON)
endforeach()

# Select optional targets
option(NASNAS_EXAMPLES     "Build the example applications"          OFF)
option(NASNAS_BUILD_SFML   "Download and build SFML as a subproject" OFF)
if (MSVC)
    option(NASNAS_STATIC_VCRT "Use /MT option instead of /MD for static VC runtimes" OFF)
endif()

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
log_targets(ARCHIVE)
log_targets(LIBRARY)
log_targets(RUNTIME)
log_targets(EXECUTABLE)

if (NASNAS_EXAMPLES)
    log_status("Custom targets available :")
    log_list_item("NasNas_examples")
endif()

# export and install targets
NasNas_export_install()
