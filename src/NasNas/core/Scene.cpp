/**
* Created by Modar Nasser on 19/04/2020.
**/


#include "NasNas/core/Scene.hpp"
#include "NasNas/core/Camera.hpp"

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
    for (const auto& drawable_variant: m_default_layer.getDrawables()) {
        drawVariant(drawable_variant, target, states);
    }
    for (const auto& [key, layer]: m_layers) {
        for (const auto& drawable_variant: layer.getDrawables()) {
            drawVariant(drawable_variant, target, states);
        }
    }
}

void Scene::drawVariant(const Layer::DrawablesTypes& variant, sf::RenderTarget& target, sf::RenderStates states) const {
    std::visit([&](auto&& drawable){
        if (m_render_bounds.intersects(drawable->getGlobalBounds())) {
            target.draw(*drawable, states);
        }
    }, variant);
    if (std::holds_alternative<const ns::DrawableTransformable*>(variant)) {
        std::get<const ns::DrawableTransformable*>(variant)->changed = false;
    }
}
