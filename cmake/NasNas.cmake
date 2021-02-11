if (NOT NASNAS_PATH)
    set(NASNAS_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    message(STATUS "Found NasNas in ${NASNAS_PATH}")
endif()

add_definitions(-DNS_DATA)
include(${NASNAS_PATH}/cmake/Data.cmake)

add_definitions(-DNS_CORE)
include(${NASNAS_PATH}/cmake/Core.cmake)

if(NASNAS_BUILD_RESLIB)
    message(STATUS "NasNas : \"reslib\" module is enabled")
    add_definitions(-DNS_RESLIB)
    include(${NASNAS_PATH}/cmake/Reslib.cmake)
endif()

if(NASNAS_BUILD_ECS)
    message(STATUS "NasNas : \"ecs\" module is enabled")
    add_definitions(-DNS_ECS)
    include(${NASNAS_PATH}/cmake/Ecs.cmake)
endif()

if(NASNAS_BUILD_TILEMAPPING)
    message(STATUS "NasNas : \"tilemapping\" module is enabled")
    add_definitions(-DNS_TILEMAPPING)
    include(${NASNAS_PATH}/cmake/Tilemapping.cmake)
endif()

if(NASNAS_BUILD_UI)
    message(STATUS "NasNas : \"ui\" module is enabled")
    add_definitions(-DNS_UI)
    include(${NASNAS_PATH}/cmake/Ui.cmake)
endif()
