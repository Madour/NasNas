set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/reslib)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/reslib)

set(
        SRC

        ${SRC_PATH}/ResourceLoader.cpp
        ${SRC_PATH}/ResourceManager.cpp
)

set(
        INC

        ${INC_PATH}/ResourceLoader.hpp
        ${INC_PATH}/ResourceManager.hpp
)

set(NasNas_Reslib_Src "${SRC}" PARENT_SCOPE)
set(NasNas_Reslib_Inc "${INC}" PARENT_SCOPE)

NasNas_add_module(reslib "${SRC}" "${INC}")
