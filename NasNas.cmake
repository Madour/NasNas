set(
    NasNas_Sources

    src/NasNas/thirdparty/pugixml.cpp

    src/NasNas/data/AppComponent.cpp
    src/NasNas/data/Config.cpp
    src/NasNas/data/Rect.cpp
    src/NasNas/data/Arial.cpp

    src/NasNas/reslib/ResourceLoader.cpp
    src/NasNas/reslib/ResourceManager.cpp

    src/NasNas/ecs/BaseEntity.cpp
    src/NasNas/ecs/BaseComponent.cpp
    src/NasNas/ecs/GraphicsComponent.cpp
    src/NasNas/ecs/SpriteComponent.cpp
    src/NasNas/ecs/ShapeComponent.cpp
    src/NasNas/ecs/PhysicsComponent.cpp
    src/NasNas/ecs/InputsComponent.cpp

    src/NasNas/core/App.cpp
    src/NasNas/core/Scene.cpp
    src/NasNas/core/Layers.cpp
    src/NasNas/core/Camera.cpp
    src/NasNas/core/Window.cpp

    src/NasNas/core/Anim.cpp
    src/NasNas/core/Spritesheet.cpp
    src/NasNas/core/BitmapText.cpp

    src/NasNas/core/Logger.cpp
    src/NasNas/core/Debug.cpp
)

set(
    NasNas_Headers

    include/NasNas/thirdparty/pugixml.hpp

    include/NasNas/data/AppComponent.hpp
    include/NasNas/data/Config.hpp
    include/NasNas/data/Rect.hpp
    include/NasNas/data/Arial.hpp

    include/NasNas/reslib/ResourceLoader.hpp
    include/NasNas/reslib/ResourceManager.hpp

    include/NasNas/ecs/BaseEntity.hpp
    include/NasNas/ecs/BaseComponent.hpp
    include/NasNas/ecs/GraphicsComponent.hpp
    include/NasNas/ecs/SpriteComponent.hpp
    include/NasNas/ecs/ShapeComponent.hpp
    include/NasNas/ecs/PhysicsComponent.hpp
    include/NasNas/ecs/InputsComponent.hpp

    include/NasNas/core/App.hpp
    include/NasNas/core/Scene.hpp
    include/NasNas/core/Layers.hpp
    include/NasNas/core/Camera.hpp
    include/NasNas/core/Window.hpp

    include/NasNas/core/Anim.hpp
    include/NasNas/core/Spritesheet.hpp
    include/NasNas/core/BitmapText.hpp

    include/NasNas/core/Logger.hpp
    include/NasNas/core/Debug.hpp
)