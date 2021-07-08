set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/ecs)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/ecs)

set(
        SRC

        ${SRC_PATH}/BaseEntity.cpp
        ${SRC_PATH}/BaseComponent.cpp
        ${SRC_PATH}/ComponentGroup.cpp
        ${SRC_PATH}/SpriteComponent.cpp
        ${SRC_PATH}/TransformComponent.cpp
        ${SRC_PATH}/PhysicsComponent.cpp
        ${SRC_PATH}/InputsComponent.cpp
        ${SRC_PATH}/ColliderComponent.cpp
)

set(
        INC

        ${INC_PATH}/BaseEntity.hpp
        ${INC_PATH}/BaseComponent.hpp
        ${INC_PATH}/ComponentGroup.hpp
        ${INC_PATH}/GraphicsComponent.hpp
        ${INC_PATH}/SpriteComponent.hpp
        ${INC_PATH}/ShapeComponent.hpp
        ${INC_PATH}/TransformComponent.hpp
        ${INC_PATH}/PhysicsComponent.hpp
        ${INC_PATH}/InputsComponent.hpp
        ${INC_PATH}/ColliderComponent.hpp
)

NasNas_create_module(Ecs "${SRC}" "${INC}")
