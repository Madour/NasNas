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

get_property(NasNas_Targets GLOBAL PROPERTY NASNAS_TARGETS)

# build tree export
export(TARGETS NasNas;${NasNas_Targets} FILE ${CMAKE_CURRENT_BINARY_DIR}/NasNas.cmake NAMESPACE NasNas::)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
# generate NasNasConfig.cmake
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/NasNasConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/NasNasConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas
)
# install NasNasConfig.cmake file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/NasNasConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas)
# install headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/NasNas DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# export targets
install(TARGETS NasNas;${NasNas_Targets} EXPORT NasNasTargets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
# install exported targets
install(EXPORT NasNasTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NasNas NAMESPACE NasNas::)
# install license and readme
install(FILES ${PROJECT_SOURCE_DIR}/LICENSE.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES ${PROJECT_SOURCE_DIR}/README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
