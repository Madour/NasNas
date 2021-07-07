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

set(NasNas_Ui_Src "${SRC}" PARENT_SCOPE)
set(NasNas_Ui_Inc "${INC}" PARENT_SCOPE)

NasNas_add_module(Ui "${SRC}" "${INC}")
