cmake_minimum_required(VERSION 3.10)

project(NasNas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_ROOT C:/SFML)
    find_package(SFML COMPONENTS graphics audio PATHS ${SFML_ROOT}/lib/cmake/ )
else()
    find_package(SFML COMPONENTS graphics audio )
endif()


set(NASNAS_BUILD_ECS            TRUE)
set(NASNAS_BUILD_RESLIB         TRUE)
set(NASNAS_BUILD_TILEMAPPING    TRUE)
set(NASNAS_BUILD_UI             TRUE)

include(cmake/NasNas.cmake)

file(COPY example/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable( NasNas_demo
    NasNas.h ${NasNas_Src} ${NasNas_Inc}
    main.cpp
    example/Game.cpp example/Game.hpp
    example/Wall.cpp example/Wall.hpp
    example/Player.cpp example/Player.hpp
    example/ShaderTransition.cpp example/ShaderTransition.hpp
)
add_library(NasNas_static STATIC ${NasNas_Src} ${NasNas_Inc})
add_library(NasNas_shared SHARED ${NasNas_Src} ${NasNas_Inc})

# Static lib target
target_include_directories(NasNas_static PRIVATE include)
target_link_libraries(NasNas_static sfml-graphics sfml-audio)

# Shared lib target
target_include_directories(NasNas_shared PRIVATE include)
target_link_libraries(NasNas_shared sfml-graphics sfml-audio)

# Demo game target
target_include_directories(NasNas_demo PRIVATE include)
target_link_libraries(NasNas_demo sfml-graphics sfml-audio)
