// Created by Modar Nasser on 01/07/2021.

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "NasNas/thirdparty/pugixml.hpp"

namespace ns::tm {
    class TiledMap;
    class TileLayer;
    class ObjectLayer;
    class GroupLayer;

    class LayersContainer {
        std::unordered_map<std::string, std::unique_ptr<TileLayer>> m_tilelayers;
        std::unordered_map<std::string, std::unique_ptr<ObjectLayer>> m_objectlayers;
        std::unordered_map<std::string, std::unique_ptr<GroupLayer>> m_grouplayers;
    public:
        LayersContainer();
        virtual ~LayersContainer();
        auto hasLayer(const std::string& name) const -> bool;
        auto getTileLayer(const std::string& name) const -> TileLayer&;
        auto getObjectLayer(const std::string& name) const -> ObjectLayer&;
        auto getGroupLayer(const std::string& name) const -> GroupLayer&;
    protected:
        void addTileLayer(const pugi::xml_node& xml_node, TiledMap* tiled_map);
        void addObjectLayer(const pugi::xml_node& xml_node, TiledMap* tiled_map);
        void addGroupLayer(const pugi::xml_node& xml_node, TiledMap* tiled_map);
        auto allTileLayers() -> decltype(m_tilelayers)&;
        auto allObjectLayers() -> decltype(m_objectlayers)&;
        auto allGroupLayers() -> decltype(m_grouplayers)&;
    };
}
