set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/core/android)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/core/android)

set(
        SRC

        ${SRC}
        ${SRC_PATH}/Activity.cpp
        ${SRC_PATH}/JavaWrapper.cpp
        ${SRC_PATH}/JniManager.cpp

        PARENT_SCOPE
)

set(
        INC

        ${INC}
        ${INC_PATH}/Activity.hpp
        ${SRC_PATH}/JavaClasses.hpp
        ${SRC_PATH}/JavaWrapper.hpp
        ${SRC_PATH}/JavaWrapperFwd.hpp
        ${SRC_PATH}/JniManager.hpp

        PARENT_SCOPE
)
