/**
* Created by Modar Nasser on 19/04/2020.
**/

#include "NasNas/core/Scene.hpp"

using namespace ns;


Scene::Scene(int width, int height) {
    m_render_texture.create(width, height);
    m_sprite.setTexture(m_render_texture.getTexture());
}

void Scene::addLayer(const std::shared_ptr<Layer>& layer, int order) {
    m_layers[std::pair<int, std::string>(order, layer->getName())] = std::make_shared<Layer>(*layer);
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
    std::cout << "Your Scene has no Layer name " << name << std::endl;
    exit(-1);
}

auto Scene::getWidth() -> int { return m_render_texture.getSize().x;}
auto Scene::getHeight() -> int { return m_render_texture.getSize().y;}

void Scene::render() {
    m_render_texture.clear(m_clear_color);
    for (auto& [key, layer]: m_layers) {
        m_render_texture.draw(*layer);
    }
    m_render_texture.display();
    m_sprite.setTexture(m_render_texture.getTexture());
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
