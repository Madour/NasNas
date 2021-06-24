set(

        NasNas_Src

        ${NasNas_Src}

        ${NASNAS_PATH}/src/NasNas/thirdparty/pugixml.cpp

        ${NASNAS_PATH}/src/NasNas/tilemapping/PropertiesContainer.cpp
        ${NASNAS_PATH}/src/NasNas/tilemapping/Layer.cpp
        ${NASNAS_PATH}/src/NasNas/tilemapping/TileLayer.cpp
        ${NASNAS_PATH}/src/NasNas/tilemapping/ObjectLayer.cpp
        ${NASNAS_PATH}/src/NasNas/tilemapping/TiledMap.cpp
        ${NASNAS_PATH}/src/NasNas/tilemapping/Tileset.cpp
        ${NASNAS_PATH}/src/NasNas/tilemapping/Tile.cpp

)

set(
        NasNas_Inc

        ${NasNas_Inc}

        ${NASNAS_PATH}/include/NasNas/thirdparty/pugixml.hpp

        ${NASNAS_PATH}/include/NasNas/tilemapping/PropertiesContainer.hpp
        ${NASNAS_PATH}/include/NasNas/tilemapping/Layer.hpp
        ${NASNAS_PATH}/include/NasNas/tilemapping/TileLayer.hpp
        ${NASNAS_PATH}/include/NasNas/tilemapping/ObjectLayer.hpp
        ${NASNAS_PATH}/include/NasNas/tilemapping/TiledMap.hpp
        ${NASNAS_PATH}/include/NasNas/tilemapping/Tileset.hpp
        ${NASNAS_PATH}/include/NasNas/tilemapping/Tile.hpp
)
