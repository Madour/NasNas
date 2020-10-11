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

# set NasNas parameters and include NasNas.cmake module
set(NASNAS_BUILD_ECS            TRUE)
set(NASNAS_BUILD_RESLIB         TRUE)
set(NASNAS_BUILD_TILEMAPPING    TRUE)
set(NASNAS_BUILD_UI             TRUE)

include(cmake/NasNas.cmake)

# copy example assets to bin
file(COPY example/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Static lib target
add_library(NasNas_static STATIC ${NasNas_Src} ${NasNas_Inc})
target_include_directories(NasNas_static PRIVATE include)
target_link_libraries(NasNas_static sfml-graphics sfml-audio)

# Shared lib target
add_library(NasNas_shared SHARED ${NasNas_Src} ${NasNas_Inc})
target_include_directories(NasNas_shared PRIVATE include)
target_link_libraries(NasNas_shared sfml-graphics sfml-audio)

# Demo game target
add_executable( NasNas_demo
    main.cpp
    example/Game.cpp example/Game.hpp
    example/Wall.cpp example/Wall.hpp
    example/Player.cpp example/Player.hpp
    example/ShaderTransition.cpp example/ShaderTransition.hpp
)
target_include_directories(NasNas_demo PRIVATE include)
target_link_libraries(NasNas_demo sfml-graphics sfml-audio NasNas_static)

