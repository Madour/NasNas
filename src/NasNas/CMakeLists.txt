set(NasNas_Selected_Modules "")

# macro to create a module target, must be called only from modules subdirectories
macro(NasNas_create_module name src inc)
    set(NasNas_${name}_Src "${src}" PARENT_SCOPE)
    set(NasNas_${name}_Inc "${inc}" PARENT_SCOPE)
    set(NasNas_Selected_Modules "${NasNas_Selected_Modules};${name}" PARENT_SCOPE)
    NasNas_add_module_target(${name} "${src}" "${inc}")
endmacro()

if (ANDROID)
    add_definitions(-DNS_ANDROID)
    if (NASNAS_BUILD_RESLIB)
        log_status("Module Reslib will be disabled because it is not compatible with Android")
        set(NASNAS_BUILD_RESLIB OFF)
    endif()
endif()

set(NasNas_Active_Options "CORE")
foreach(module_name ${NASNAS_MODULES})
    if (NASNAS_BUILD_${module_name})
        list(APPEND NasNas_Active_Options ${module_name})
    endif()
endforeach()

foreach(module_name ${NasNas_Active_Options})
    add_definitions(-DNS_${module_name})
endforeach()

foreach(module_name ${NasNas_Active_Options})
    string(TOLOWER ${module_name} module_name_lowercase)
    add_subdirectory(${module_name_lowercase})
endforeach()

set(NasNas_Src "")
set(NasNas_Inc "")

foreach(module ${NasNas_Selected_Modules})
    set(NasNas_Src "${NasNas_Src};${NasNas_${module}_Src}")
    set(NasNas_Inc "${NasNas_Inc};${NasNas_${module}_Inc}")
endforeach()

set(type "STATIC")
if (ANDROID)
    set(type "SHARED")
endif()

add_library(NasNas ${type} ${NasNas_Src} ${NasNas_Inc})
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

if (ANDROID)
    NasNas_register_target(NasNas LIBRARY)
else()
    NasNas_register_target(NasNas ARCHIVE)
endif()
