// Created by Modar Nasser on 01/07/2021.

#pragma once

#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/tilemapping/ObjectLayer.hpp"

namespace ns::tm {
    class LayersContainer : public PropertiesContainer {
        std::unordered_map<std::string, std::unique_ptr<TileLayer>> m_tilelayers;
        std::unordered_map<std::string, std::unique_ptr<ObjectLayer>> m_objectlayers;
    public:
        auto hasLayer(const std::string& name) const -> bool;
        auto getTileLayer(const std::string& name) const -> TileLayer&;
        auto getObjectLayer(const std::string& name) const -> ObjectLayer&;
    protected:
        void addTileLayer(const pugi::xml_node& xml_node, TiledMap* tiled_map);
        void addObjectLayer(const pugi::xml_node& xml_node, TiledMap* tiled_map);
        auto allTileLayers() -> decltype(m_tilelayers)&;
        auto allObjectLayers() -> decltype(m_objectlayers)&;
    };
}
