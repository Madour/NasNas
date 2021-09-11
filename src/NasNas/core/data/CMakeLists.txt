set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/core/data)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/core/data)

set(
        SRC

        ${SRC}
        ${SRC_PATH}/Arial.cpp
        ${SRC_PATH}/Config.cpp
        ${SRC_PATH}/Logger.cpp
        ${SRC_PATH}/ShaderHolder.cpp
        ${SRC_PATH}/Utils.cpp

        PARENT_SCOPE
)

set(
        INC

        ${INC}
        ${INC_PATH}/Arial.hpp
        ${INC_PATH}/Config.hpp
        ${INC_PATH}/Logger.hpp
        ${INC_PATH}/Maths.hpp
        ${INC_PATH}/Rect.hpp
        ${INC_PATH}/Introspection.hpp
        ${INC_PATH}/ShaderHolder.hpp
        ${INC_PATH}/Singleton.hpp
        ${INC_PATH}/Utils.hpp

        PARENT_SCOPE
)
