cmake_minimum_required(VERSION 3.15)

project(NasNas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    find_package(SFML COMPONENTS graphics audio PATHS C:/SFML/lib/cmake/ )
else()
    find_package(SFML COMPONENTS graphics audio )
endif()

include(NasNas.cmake)

file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


add_executable(NasNas
        main.cpp main.hpp
        example/Game.cpp example/Game.hpp
        example/Player.cpp example/Player.hpp

        NasNas.h ${NasNas_Sources} ${NasNas_Headers}
        )

target_include_directories(NasNas PRIVATE ${NasNas_Include_Dir})

target_link_libraries(NasNas sfml-graphics)
