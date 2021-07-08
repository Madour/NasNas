message(STATUS "NasNas : enabled modules :")

add_definitions(-DNS_CORE)
add_subdirectory(core)

if(NASNAS_BUILD_RESLIB)
    add_definitions(-DNS_RESLIB)
    add_subdirectory(reslib)
endif()

if(NASNAS_BUILD_ECS)
    add_definitions(-DNS_ECS)
    add_subdirectory(ecs)
endif()

if(NASNAS_BUILD_TILEMAPPING)
    add_definitions(-DNS_TILEMAPPING)
    add_subdirectory(tilemapping)
endif()

if(NASNAS_BUILD_UI)
    add_definitions(-DNS_UI)
    add_subdirectory(ui)
endif()

set(NasNas_Src "")
set(NasNas_Inc "")
set(NasNas_Modules_Names "Core;Reslib;Ecs;Tilemapping;Ui")

foreach(module ${NasNas_Modules_Names})
    set(NasNas_Src "${NasNas_Src};${NasNas_${module}_Src}")
    set(NasNas_Inc "${NasNas_Inc};${NasNas_${module}_Inc}")
endforeach()

add_library(NasNas STATIC ${NasNas_Src} ${NasNas_Inc})
target_include_directories(NasNas PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(NasNas PUBLIC $<INSTALL_INTERFACE:include>)
target_link_libraries(NasNas PUBLIC ${NasNas_Libs})
set_target_properties(
        NasNas
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        DEBUG_POSTFIX -d
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib
        EXPORT_NAME All
)
add_library(NasNas::All ALIAS NasNas)

install(TARGETS NasNas EXPORT NasNasTargets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

NasNas_register_target(NasNas)
