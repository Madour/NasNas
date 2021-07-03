set(SRC_PATH ${PROJECT_SOURCE_DIR}/src/NasNas/tilemapping)
set(INC_PATH ${PROJECT_SOURCE_DIR}/include/NasNas/tilemapping)

set(
        SRC

        ${SRC_PATH}/../thirdparty/pugixml.cpp

        ${SRC_PATH}/PropertiesContainer.cpp
        ${SRC_PATH}/LayersContainer.cpp
        ${SRC_PATH}/TiledMap.cpp
        ${SRC_PATH}/Tileset.cpp
        ${SRC_PATH}/Layer.cpp
        ${SRC_PATH}/TileLayer.cpp
        ${SRC_PATH}/Tile.cpp
        ${SRC_PATH}/ObjectLayer.cpp
        ${SRC_PATH}/Object.cpp
        ${SRC_PATH}/GroupLayer.cpp
)

set(
        INC

        ${INC_PATH}/../thirdparty/pugixml.hpp

        ${INC_PATH}/PropertiesContainer.hpp
        ${INC_PATH}/LayersContainer.hpp
        ${INC_PATH}/TiledMap.hpp
        ${INC_PATH}/Tileset.hpp
        ${INC_PATH}/Layer.hpp
        ${INC_PATH}/TileLayer.hpp
        ${INC_PATH}/Tile.hpp
        ${INC_PATH}/ObjectLayer.hpp
        ${INC_PATH}/Object.hpp
        ${INC_PATH}/GroupLayer.hpp
)

set(NasNas_Tilemapping_Src "${SRC}" PARENT_SCOPE)
set(NasNas_Tilemapping_Inc "${INC}" PARENT_SCOPE)

NasNas_add_module(tilemapping "${SRC}" "${INC}")
