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

void LayersContainer::update(const Camera* cam) {
    sf::Vector2f parallax_offset{1.f, 1.f};

    for (auto& [name, group] : m_grouplayers) {
        group->update(cam);
    }

    for (auto& [name, layer] : m_tilelayers) {
        layer->update();
        if (cam) {
            layer->setPosition((parallax_offset - layer->getTotalParallaxFactor()) * cam->getPosition() + layer->getOffset());
        }
    }

    if (cam) {
        for (auto& [name, layer] : m_objectlayers) {
            layer->setPosition((parallax_offset - layer->getTotalParallaxFactor()) * cam->getPosition() + layer->getOffset());
        }
    }
}

void LayersContainer::parseLayers(const pugi::xml_node& xml_node, TiledMap* tiledmap) {
    for (auto& child : xml_node.children()) {
        std::string child_name{child.name()};
        Layer* new_layer = nullptr;
        if (child_name == "layer") {
            new_layer = addTileLayer(child, tiledmap);
        }
        else if (child_name == "objectgroup") {
            new_layer = addObjectLayer(child, tiledmap);
        }
        else if (child_name == "group") {
            new_layer = addGroupLayer(child, tiledmap);
        }
        if (tiledmap != this && new_layer)
            new_layer->m_parent_group = dynamic_cast<GroupLayer*>(this);
    }
}

auto LayersContainer::addTileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) -> Layer* {
    auto new_layer = std::make_unique<TileLayer>(xml_node, tiledmap);
    auto layer_name = new_layer->getName();
    m_tilelayers[layer_name] = std::move(new_layer);
    m_layers.push_back(m_tilelayers.at(layer_name).get());
    return m_layers.back();
}

auto LayersContainer::addObjectLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) -> Layer* {
    auto new_layer = std::make_unique<ObjectLayer>(xml_node, tiledmap);
    auto layer_name = new_layer->getName();
    m_objectlayers[layer_name] = std::move(new_layer);
    m_layers.push_back(m_objectlayers.at(layer_name).get());
    return m_layers.back();
}

auto LayersContainer::addGroupLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) -> Layer* {
    auto new_layer = std::make_unique<GroupLayer>(xml_node, tiledmap);
    auto layer_name = new_layer->getName();
    m_grouplayers[layer_name] = std::move(new_layer);
    m_layers.push_back(m_grouplayers.at(layer_name).get());
    return m_layers.back();
}

auto LayersContainer::allTileLayers() const -> const decltype(m_tilelayers)& {
    return m_tilelayers;
}

auto LayersContainer::allObjectLayers() const -> const decltype(m_objectlayers)& {
    return m_objectlayers;
}

auto LayersContainer::allGroupLayers() const -> const decltype(m_grouplayers)& {
    return m_grouplayers;
}

auto LayersContainer::allLayers() const -> const decltype(m_layers)& {
    return m_layers;
}
