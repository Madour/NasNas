/**
* Created by Modar Nasser on 19/04/2020.
**/

#include "NasNas/core/Scene.hpp"

using namespace ns;


Scene::Scene(const std::string& name) {
    m_name = name;
}

void Scene::addLayer(Layer* layer, int order) {
    m_layers[std::pair<int, std::string>(order, layer->getName())] = std::shared_ptr<Layer>(layer);
}

void Scene::addLayer(std::shared_ptr<Layer>& layer, int order) {
    m_layers[std::pair<int, std::string>(order, layer->getName())] = layer;
}

auto Scene::getLayer(int order) -> Layer* {
    for (auto [key, value] : m_layers) {
        if (key.first == order)
            return value.get();
    }
    std::cout << "Your Scene has no Layer " << order << std::endl;
    exit(-1);
}

auto Scene::getLayer(const std::string& name) -> Layer* {
    for (auto [key, value] : m_layers) {
        if (key.second == name)
            return value.get();
    }
    std::cout << "Your Scene has no Layer named " << name << std::endl;
    exit(-1);
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto & [key, layer]: m_layers) {
        target.draw(*layer, states);
    }
}
