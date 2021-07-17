set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/tween)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/tween)

set(
        SRC

        ${SRC_PATH}/Tween.cpp
)

set(
        INC

        ${INC_PATH}/Tween.hpp
)

NasNas_create_module(Tween "${SRC}" "${INC}")
