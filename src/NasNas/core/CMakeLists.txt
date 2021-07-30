set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/core)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/core)

set(
        SRC

        ${SRC_PATH}/data/AppComponent.cpp
        ${SRC_PATH}/data/Arial.cpp
        ${SRC_PATH}/data/Config.cpp
        ${SRC_PATH}/data/Logger.cpp
        ${SRC_PATH}/data/ShaderHolder.cpp
        ${SRC_PATH}/data/Utils.cpp

        ${SRC_PATH}/graphics/Anim.cpp
        ${SRC_PATH}/graphics/BitmapText.cpp
        ${SRC_PATH}/graphics/ParticleSystem.cpp
        ${SRC_PATH}/graphics/Renderable.cpp
        ${SRC_PATH}/graphics/Shapes.cpp
        ${SRC_PATH}/graphics/Sprite.cpp
        ${SRC_PATH}/graphics/SpriteBatch.cpp
        ${SRC_PATH}/graphics/Spritesheet.cpp
        ${SRC_PATH}/graphics/Transformable.cpp
        ${SRC_PATH}/graphics/VertexArray.cpp

        ${SRC_PATH}/App.cpp
        ${SRC_PATH}/Camera.cpp
        ${SRC_PATH}/Debug.cpp
        ${SRC_PATH}/Layer.cpp
        ${SRC_PATH}/Scene.cpp
        ${SRC_PATH}/Transition.cpp
        ${SRC_PATH}/Window.cpp
)

set(
        INC

        ${INC_PATH}/data/AppComponent.hpp
        ${INC_PATH}/data/Arial.hpp
        ${INC_PATH}/data/Config.hpp
        ${INC_PATH}/data/Logger.hpp
        ${INC_PATH}/data/Maths.hpp
        ${INC_PATH}/data/Rect.hpp
        ${INC_PATH}/data/Rtti.hpp
        ${INC_PATH}/data/ShaderHolder.hpp
        ${INC_PATH}/data/Utils.hpp

        ${INC_PATH}/graphics/Anim.hpp
        ${INC_PATH}/graphics/BitmapText.hpp
        ${INC_PATH}/graphics/Shapes.hpp
        ${INC_PATH}/graphics/ParticleSystem.hpp
        ${INC_PATH}/graphics/Renderable.hpp
        ${INC_PATH}/graphics/Sprite.hpp
        ${INC_PATH}/graphics/SpriteBatch.hpp
        ${INC_PATH}/graphics/Spritesheet.hpp
        ${INC_PATH}/graphics/Transformable.hpp
        ${INC_PATH}/graphics/VertexArray.hpp

        ${INC_PATH}/App.hpp
        ${INC_PATH}/Camera.hpp
        ${INC_PATH}/Debug.hpp
        ${INC_PATH}/Layer.hpp
        ${INC_PATH}/Scene.hpp
        ${INC_PATH}/Transition.hpp
        ${INC_PATH}/Window.hpp
)

NasNas_create_module(Core "${SRC}" "${INC}")
