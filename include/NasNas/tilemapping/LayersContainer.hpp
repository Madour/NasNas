// Created by Modar Nasser on 01/07/2021.

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "NasNas/thirdparty/pugixml.hpp"
#include "NasNas/core/Camera.hpp"

namespace ns::tm {
    class TiledMap;
    class Layer;
    class TileLayer;
    class ObjectLayer;
    class ImageLayer;
    class GroupLayer;

    class LayersContainer {
        std::unordered_map<std::string, std::unique_ptr<TileLayer>> m_tilelayers;
        std::unordered_map<std::string, std::unique_ptr<ObjectLayer>> m_objectlayers;
        std::unordered_map<std::string, std::unique_ptr<GroupLayer>> m_grouplayers;
        std::unordered_map<std::string, std::unique_ptr<ImageLayer>> m_imagelayers;
        std::vector<Layer*> m_layers;

    public:
        LayersContainer() = default;
        virtual ~LayersContainer() = default;

        auto hasLayer(const std::string& name) const -> bool;
        auto getTileLayer(const std::string& name) const -> TileLayer&;
        auto getObjectLayer(const std::string& name) const -> ObjectLayer&;
        auto getImageLayer(const std::string& name) const -> ImageLayer&;
        auto getGroupLayer(const std::string& name) const -> GroupLayer&;

        void update(const Camera* cam);

    protected:
        void parseLayers(const pugi::xml_node& xml_node, TiledMap* tiledmap);

        auto addTileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) -> Layer*;
        auto addObjectLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) -> Layer*;
        auto addImageLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) -> Layer*;
        auto addGroupLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) -> Layer*;

        auto allTileLayers() const -> const decltype(m_tilelayers)&;
        auto allObjectLayers() const -> const decltype(m_objectlayers)&;
        auto allImageLayers() const -> const decltype(m_imagelayers)&;
        auto allGroupLayers() const -> const decltype(m_grouplayers)&;
        auto allLayers() const -> const decltype(m_layers)&;
    };
}
