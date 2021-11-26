set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/ui)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/ui)

set(
        SRC

        ${SRC_PATH}/Button.cpp
        ${SRC_PATH}/Container.cpp
        ${SRC_PATH}/GuiRoot.cpp
        ${SRC_PATH}/NineSlice.cpp
        ${SRC_PATH}/Style.cpp
        ${SRC_PATH}/TypedText.cpp
        ${SRC_PATH}/Widget.cpp
)

set(
        INC

        ${INC_PATH}/Button.hpp
        ${INC_PATH}/Callbacks.hpp
        ${INC_PATH}/Container.hpp
        ${INC_PATH}/GuiRoot.hpp
        ${INC_PATH}/NineSlice.hpp
        ${INC_PATH}/Style.hpp
        ${INC_PATH}/TypedText.hpp
        ${INC_PATH}/Widget.hpp
)

NasNas_create_module(Ui "${SRC}" "${INC}")
