// Created by Modar Nasser on 01/07/2021.

#include "NasNas/tilemapping/LayersContainer.hpp"

#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/tilemapping/ObjectLayer.hpp"
#include "NasNas/tilemapping/GroupLayer.hpp"

using namespace ns;
using namespace ns::tm;

LayersContainer::LayersContainer() = default;
LayersContainer::~LayersContainer() = default;

auto LayersContainer::hasLayer(const std::string& name) const -> bool {
    return (m_tilelayers.count(name) > 0 || m_objectlayers.count(name) > 0);
}

auto LayersContainer::getTileLayer(const std::string& name) const -> TileLayer& {
    if (m_tilelayers.count(name) > 0)
        return *m_tilelayers.at(name);
    std::cerr << "No TileLayer named «" << name << "» was found." << std::endl;
    exit(-1);
}

auto LayersContainer::getObjectLayer(const std::string& name) const -> ObjectLayer& {
    if (m_objectlayers.count(name) > 0)
        return *m_objectlayers.at(name);
    std::cerr << "No ObjectLayer named «" << name << "» was found." << std::endl;
    exit(-1);
}

auto LayersContainer::getGroupLayer(const std::string& name) const -> GroupLayer& {
    if (m_grouplayers.count(name) > 0)
        return *m_grouplayers.at(name);
    std::cerr << "No GroupLayer named «" << name << "» was found." << std::endl;
    exit(-1);
}

void LayersContainer::addTileLayer(const pugi::xml_node& xml_node, TiledMap* tiled_map) {
    auto new_layer = std::make_unique<TileLayer>(xml_node, tiled_map);
    m_tilelayers[new_layer->getName()] = std::move(new_layer);
}

void LayersContainer::addObjectLayer(const pugi::xml_node& xml_node, TiledMap* tiled_map) {
    auto new_layer = std::make_unique<ObjectLayer>(xml_node, tiled_map);
    m_objectlayers[new_layer->getName()] = std::move(new_layer);
}

void LayersContainer::addGroupLayer(const pugi::xml_node& xml_node, TiledMap* tiled_map) {
    auto new_layer = std::make_unique<GroupLayer>(xml_node, tiled_map);
    m_grouplayers[new_layer->getName()] = std::move(new_layer);
}

auto LayersContainer::allTileLayers() -> decltype(m_tilelayers)& {
    return m_tilelayers;
}

auto LayersContainer::allObjectLayers() -> decltype(m_objectlayers)& {
    return m_objectlayers;
}

auto LayersContainer::allGroupLayers() -> decltype(m_grouplayers)& {
    return m_grouplayers;
}
