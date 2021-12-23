set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/core/graphics)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/core/graphics)

set(
        SRC

        ${SRC}
        ${SRC_PATH}/Anim.cpp
        ${SRC_PATH}/BitmapText.cpp
        ${SRC_PATH}/ParticleSystem.cpp
        ${SRC_PATH}/Renderable.cpp
        ${SRC_PATH}/Shapes.cpp
        ${SRC_PATH}/Sprite.cpp
        ${SRC_PATH}/SpriteBatch.cpp
        ${SRC_PATH}/SpriteSheet.cpp
        ${SRC_PATH}/Transformable.cpp
        ${SRC_PATH}/VertexArray.cpp

        PARENT_SCOPE
)

set(
        INC

        ${INC}
        ${INC_PATH}/Anim.hpp
        ${INC_PATH}/BitmapText.hpp
        ${INC_PATH}/Shapes.hpp
        ${INC_PATH}/ParticleSystem.hpp
        ${INC_PATH}/Renderable.hpp
        ${INC_PATH}/Sprite.hpp
        ${INC_PATH}/SpriteBatch.hpp
        ${INC_PATH}/SpriteSheet.hpp
        ${INC_PATH}/Transformable.hpp
        ${INC_PATH}/VertexArray.hpp

        PARENT_SCOPE
)
