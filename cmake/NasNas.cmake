set(NasNas_Src "")
set(NasNas_Inc "")

add_definitions(-DNS_DATA)
include(cmake/Data.cmake)

add_definitions(-DNS_CORE)
include(cmake/Core.cmake)

if(NASNAS_BUILD_RESLIB)
    message(STATUS "NasNas : Will build \"reslib\" module")
    add_definitions(-DNS_RESLIB)
    include(cmake/Reslib.cmake)
endif()

if(NASNAS_BUILD_ECS)
    message(STATUS "NasNas : Will build \"ecs\" module")
    add_definitions(-DNS_ECS)
    include(cmake/Ecs.cmake)
endif()

if(NASNAS_BUILD_TILEMAPPING)
    message(STATUS "NasNas : Will build \"tilemapping\" module")
    add_definitions(-DNS_TILEMAPPING)
    include(cmake/Tilemapping.cmake)
endif()

if(NASNAS_BUILD_UI)
    message(STATUS "NasNas : Will build \"ui\" module")
    add_definitions(-DNS_UI)
    include(cmake/Ui.cmake)
endif()