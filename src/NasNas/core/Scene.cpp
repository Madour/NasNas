/**
* Created by Modar Nasser on 19/04/2020.
**/


#include <NasNas/core/Scene.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <NasNas/core/Camera.hpp>

using namespace ns;

Scene::Scene(std::string name) :
m_name(std::move(name)),
m_default_layer("")
{}

void Scene::deleteLayer(const std::string& name) {
    for (auto it = m_layers.begin(); it != m_layers.end(); ++it) {
        if (it->getName() == name) {
            it->clear();
            m_layers.erase(it);
            break;
        }
    }
}

auto Scene::getLayer(const std::string& name) -> Layer& {
    for (auto& layer : m_layers) {
        if (layer.getName() == name)
            return layer;
    }
    std::cerr << "(ns::Scene::getLayer) Scene has no Layer named " << name << std::endl;
    exit(-1);
}

auto Scene::getDefaultLayer() -> Layer& {
    return m_default_layer;
}

void Scene::temporaryLinkCamera(Camera* camera) {
    m_render_bounds = camera->getGlobalBounds();
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto* drawable : m_default_layer.allDrawables()) {
        if (m_render_bounds.intersects(m_default_layer.getDrawableBounds(drawable))) {
            target.draw(*drawable, states);
        }
    }
    for (const auto& layer : m_layers) {
        for (const auto* drawable : layer.allDrawables()) {
            if (m_render_bounds.intersects(layer.getDrawableBounds(drawable))) {
                target.draw(*drawable, states);
            }
        }
    }
}
