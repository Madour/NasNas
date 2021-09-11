set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/core)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/core)

set(
        SRC

        ${SRC_PATH}/App.cpp
        ${SRC_PATH}/AppAccess.cpp
        ${SRC_PATH}/Camera.cpp
        ${SRC_PATH}/Debug.cpp
        ${SRC_PATH}/Inputs.cpp
        ${SRC_PATH}/Layer.cpp
        ${SRC_PATH}/Scene.cpp
        ${SRC_PATH}/Transition.cpp
        ${SRC_PATH}/Window.cpp
)

set(
        INC

        ${INC_PATH}/App.hpp
        ${INC_PATH}/AppAccess.hpp
        ${INC_PATH}/AppState.hpp
        ${INC_PATH}/Camera.hpp
        ${INC_PATH}/Debug.hpp
        ${INC_PATH}/Inputs.hpp
        ${INC_PATH}/Layer.hpp
        ${INC_PATH}/Scene.hpp
        ${INC_PATH}/Transition.hpp
        ${INC_PATH}/Window.hpp
)


add_subdirectory(data)
add_subdirectory(graphics)

if (ANDROID)
    add_subdirectory(android)
endif()

NasNas_create_module(Core "${SRC}" "${INC}")
