set(NasNas_Src "")
set(NasNas_Inc "")

add_compile_definitions(NS_DATA)
include(cmake/Data.cmake)

add_compile_definitions(NS_CORE)
include(cmake/Core.cmake)

if(NASNAS_BUILD_RESLIB)
    message(STATUS "NasNas : Building reslib")
    add_compile_definitions(NS_RESLIB)
    include(cmake/Reslib.cmake)
endif()

if(NASNAS_BUILD_ECS)
    message(STATUS "NasNas : Building ecs")
    add_compile_definitions(NS_ECS)
    include(cmake/Ecs.cmake)
endif()

if(NASNAS_BUILD_TILEMAPPING)
    message(STATUS "NasNas : Building tilemapping")
    add_compile_definitions(NS_TILEMAPPING)
    include(cmake/Tilemapping.cmake)
endif()

if(NASNAS_BUILD_UI)
    message(STATUS "NasNas : Building ui")
    add_compile_definitions(NS_UI)
    include(cmake/Ui.cmake)
endif()