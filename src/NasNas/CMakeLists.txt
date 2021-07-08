message(STATUS "NasNas : enabled modules :")
set(NasNas_Modules_Names "")

macro(NasNas_create_module name src inc)
    set(NasNas_${name}_Src "${src}" PARENT_SCOPE)
    set(NasNas_${name}_Inc "${inc}" PARENT_SCOPE)
    set(NasNas_Modules_Names "${NasNas_Modules_Names};${name}" PARENT_SCOPE)
    message("   -> ${name}")

    NasNas_add_module_target(${name} "${src}" "${inc}")
endmacro()

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

foreach(module ${NasNas_Modules_Names})
    set(NasNas_Src "${NasNas_Src};${NasNas_${module}_Src}")
    set(NasNas_Inc "${NasNas_Inc};${NasNas_${module}_Inc}")
endforeach()

add_library(NasNas STATIC ${NasNas_Src} ${NasNas_Inc})
add_library(NasNas::All ALIAS NasNas)
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

NasNas_register_target(NasNas ARCHIVE)
