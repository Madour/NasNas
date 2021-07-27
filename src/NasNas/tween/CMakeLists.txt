set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/tween)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/tween)

set(SRC
        ${SRC_PATH}/Easing.cpp
        ${SRC_PATH}/Tween.cpp
)

set(INC
        ${INC_PATH}/Easing.hpp
        ${INC_PATH}/Tween.hpp
        ${INC_PATH}/MultiTween.hpp
)

NasNas_create_module(Tween "${SRC}" "${INC}")
