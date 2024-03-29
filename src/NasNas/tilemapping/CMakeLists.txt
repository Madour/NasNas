set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/tilemapping)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/tilemapping)

set(
        SRC

        ${SRC_PATH}/../thirdparty/pugixml.cpp

        ${SRC_PATH}/GroupLayer.cpp
        ${SRC_PATH}/ImageLayer.cpp
        ${SRC_PATH}/Layer.cpp
        ${SRC_PATH}/LayersContainer.cpp
        ${SRC_PATH}/Object.cpp
        ${SRC_PATH}/ObjectLayer.cpp
        ${SRC_PATH}/PropertiesContainer.cpp
        ${SRC_PATH}/Tile.cpp
        ${SRC_PATH}/TiledMap.cpp
        ${SRC_PATH}/TileLayer.cpp
        ${SRC_PATH}/Tileset.cpp
)

set(
        INC

        ${INC_PATH}/../thirdparty/pugixml.hpp

        ${INC_PATH}/GroupLayer.hpp
        ${INC_PATH}/ImageLayer.hpp
        ${INC_PATH}/Layer.hpp
        ${INC_PATH}/LayersContainer.hpp
        ${INC_PATH}/Object.hpp
        ${INC_PATH}/ObjectLayer.hpp
        ${INC_PATH}/PropertiesContainer.hpp
        ${INC_PATH}/Tile.hpp
        ${INC_PATH}/TiledMap.hpp
        ${INC_PATH}/TileLayer.hpp
        ${INC_PATH}/Tileset.hpp
)

NasNas_create_module(Tilemapping "${SRC}" "${INC}")
