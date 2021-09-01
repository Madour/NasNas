// Created by Modar Nasser on 01/07/2021.

#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/tilemapping/ObjectLayer.hpp"
#include "NasNas/tilemapping/GroupLayer.hpp"

using namespace ns;
using namespace ns::tm;

GroupLayer::GroupLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap) :
Layer(xml_node, tiledmap)
{
    parseProperties(xml_node.child("properties"));
    parseLayers(xml_node, tiledmap);
}

auto GroupLayer::getGlobalBounds() const -> ns::FloatRect {
    if (allLayers().empty()) return {};

    auto bounds = allLayers()[0]->getGlobalBounds();
    float right = bounds.right(), bottom = bounds.bottom();
    for (auto& layer : allLayers()) {
        auto layer_bounds = layer->getGlobalBounds();
        bounds.left = std::min(bounds.left, layer_bounds.left);
        bounds.top = std::min(bounds.top, layer_bounds.top);
        right = std::max(right, layer_bounds.right());
        bottom = std::max(bottom, layer_bounds.bottom());
    }
    return {bounds.left, bounds.top, right - bounds.left, bottom - bounds.top};
}

void GroupLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (auto* layer : allLayers()) {
        target.draw(*layer, states);
    }
}
