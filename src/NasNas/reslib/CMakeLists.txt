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

NasNas_create_module(Reslib "${SRC}" "${INC}")
