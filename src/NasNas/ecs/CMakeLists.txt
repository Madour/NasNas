set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/ecs)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/ecs)

set(
        SRC

        ${SRC_PATH}/EntityObject.cpp
        ${SRC_PATH}/DefaultSystems.cpp
        ${SRC_PATH}/components/SpriteComponent.cpp
        ${SRC_PATH}/components/ColliderComponent.cpp
        ${SRC_PATH}/components/InputsComponent.cpp
        ${SRC_PATH}/components/PhysicsComponent.cpp
        ${SRC_PATH}/components/TransformComponent.cpp
)

set(
        INC

        ${INC_PATH}/components/GraphicsComponent.hpp
        ${INC_PATH}/components/SpriteComponent.hpp
        ${INC_PATH}/components/ShapeComponent.hpp
        ${INC_PATH}/components/ColliderComponent.hpp
        ${INC_PATH}/components/InputsComponent.hpp
        ${INC_PATH}/components/PhysicsComponent.hpp
        ${INC_PATH}/components/TransformComponent.hpp
        ${INC_PATH}/DefaultSystems.hpp
        ${INC_PATH}/EntityObject.hpp
        ${INC_PATH}/Registry.hpp
        ${INC_PATH}/Storage.hpp
        ${INC_PATH}/System.hpp
        ${INC_PATH}/View.hpp
)

NasNas_create_module(Ecs "${SRC}" "${INC}")
