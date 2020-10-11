cmake_minimum_required(VERSION 3.10)

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
if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR C:/SFML)
    find_package(SFML COMPONENTS graphics audio PATHS ${SFML_DIR}/lib/cmake/ )
else()
    find_package(SFML COMPONENTS graphics audio )
endif()


# Select which optional modules to build
set(NASNAS_BUILD_ECS            TRUE)
set(NASNAS_BUILD_RESLIB         TRUE)
set(NASNAS_BUILD_TILEMAPPING    TRUE)
set(NASNAS_BUILD_UI             TRUE)
# Set this variable to FALSE if you don't want to build examples
set(NASNAS_BUILD_EXAMPLES       TRUE)

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
    add_subdirectory(examples)
endif()
