/**
* Created by Modar Nasser on 19/04/2020.
**/


#include "NasNas/core/Scene.hpp"
#include "NasNas/core/Camera.hpp"
#include "NasNas/core/graphics/Transformable.hpp"

using namespace ns;

Scene::Scene(std::string name) :
m_name(std::move(name)),
m_default_layer("")
{}

void Scene::addLayer(const std::string& name, int order) {
    auto ret = m_layers.emplace(order, name);
    if (!ret.second)
        std::cout << "Warning : the Scene " << m_name << " has already a Layer " << order << std::endl;
}

void Scene::removeLayer(int order) {
    if (m_layers.count(order) > 0) {
        m_layers.at(order).clear();
        m_layers.erase(order);
    }
}

void Scene::removeLayer(const std::string& name) {
    for (auto& [key, layer] : m_layers) {
        if (layer.getName() == name) {
            layer.clear();
            m_layers.erase(key);
            break;
        }
    }
}

auto Scene::getLayer(int order) -> Layer& {
    if (m_layers.count(order) > 0)
        return m_layers.at(order);
    std::cout << "Your Scene has no Layer " << order << std::endl;
    exit(-1);
}

auto Scene::getLayer(const std::string& name) -> Layer& {
    for (auto& [key, layer] : m_layers) {
        if (layer.getName() == name)
            return layer;
    }
    std::cout << "Your Scene has no Layer named " << name << std::endl;
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
        // TODO : fix cast broken because DrawableTransformable was removed
        auto drawable_transformable = dynamic_cast<const ns::Transformable*>(drawable);
        if (drawable_transformable != nullptr) {
            drawable_transformable->changed = false;
        }
    }
    for (const auto& [key, layer] : m_layers) {
        for (const auto* drawable : layer.allDrawables()) {
            if (m_render_bounds.intersects(layer.getDrawableBounds(drawable))) {
                target.draw(*drawable, states);
            }
            auto drawable_transformable = dynamic_cast<const ns::Transformable*>(drawable);
            if (drawable_transformable != nullptr) {
                drawable_transformable->changed = false;
            }
        }
    }
}
