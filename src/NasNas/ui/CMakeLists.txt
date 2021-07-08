set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/ui)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/ui)

set(
        SRC

        ${SRC_PATH}/TypedText.cpp
)

set(
        INC

        ${INC_PATH}/TypedText.hpp
)

NasNas_create_module(Ui "${SRC}" "${INC}")
