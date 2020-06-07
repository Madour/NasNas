set(NasNas_Include_Dir ${CMAKE_HOME_DIRECTORY}/include)

set(
        NasNas_Sources

        src/NasNas/thirdparty/tinyxml2.cpp
        src/NasNas/thirdparty/pugixml.cpp

        src/NasNas/data/AppComponent.cpp
        src/NasNas/data/Rect.cpp

        src/NasNas/reslib/ResourceLoader.cpp
        src/NasNas/reslib/ResourceManager.cpp

        src/NasNas/core/App.cpp
        src/NasNas/core/Camera.cpp
        src/NasNas/core/Entities.cpp
        src/NasNas/core/Layers.cpp
        src/NasNas/core/Scene.cpp
        src/NasNas/core/Window.cpp

        src/NasNas/core/Anim.cpp
        src/NasNas/core/Sprite.cpp

        src/NasNas/core/Logger.cpp
        src/NasNas/core/Debug.cpp
)

set(
        NasNas_Headers

        include/NasNas/thirdparty/tinyxml2.h
        include/NasNas/thirdparty/pugixml.hpp

        include/NasNas/data/AppComponent.hpp
        include/NasNas/data/Rect.hpp

        include/NasNas/reslib/ResourceLoader.hpp
        include/NasNas/reslib/ResourceManager.hpp

        include/NasNas/core/App.hpp
        include/NasNas/core/Camera.hpp
        include/NasNas/core/Entities.hpp
        include/NasNas/core/Layers.hpp
        include/NasNas/core/Scene.hpp
        include/NasNas/core/Window.hpp

        include/NasNas/core/Anim.hpp
        include/NasNas/core/Sprite.hpp

        include/NasNas/core/Logger.hpp
        include/NasNas/core/Debug.hpp
)