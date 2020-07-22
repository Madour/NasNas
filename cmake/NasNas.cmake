set(NasNas_Src "")
set(NasNas_Inc "")

include(cmake/Data.cmake)

include(cmake/Core.cmake)

if(NASNAS_BUILD_ECS)
    include(cmake/Ecs.cmake)
endif()

if(NASNAS_BUILD_RESLIB)
    include(cmake/Reslib.cmake)
endif()

if(NASNAS_BUILD_TILEMAPPING)
    include(cmake/Tilemapping.cmake)
endif()
