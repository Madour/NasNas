/**
* Created by Modar Nasser on 19/04/2020.
**/


#include "NasNas/core/Scene.hpp"
#include "NasNas/core/Camera.hpp"

using namespace ns;

Scene::Scene(std::string name) :
m_name(std::move(name)),
m_default_layer(new Layer(""))
{}

void Scene::addLayer(Layer* layer, int order) {
    m_layers[std::pair<int, std::string>(order, layer->getName())] = std::shared_ptr<Layer>(layer);
}

void Scene::addLayer(const std::string& name, int order) {
    m_layers[std::pair<int, std::string>(order, name)] = std::make_shared<Layer>(name);
}

void Scene::addLayer(const std::shared_ptr<Layer>& layer, int order) {
    m_layers[std::pair<int, std::string>(order, layer->getName())] = layer;
}

void Scene::removeLayer(int order) {
    for (auto [key, layer] : m_layers) {
        if (key.first == order) {
            layer->clear();
            m_layers.erase(key);
            break;
        }
    }
}

void Scene::removeLayer(const std::string& name) {
    for (auto [key, layer] : m_layers) {
        if (key.second == name) {
            layer->clear();
            m_layers.erase(key);
            break;
        }
    }
}

auto Scene::getLayer(int order) -> Layer* {
    for (auto [key, layer] : m_layers) {
        if (key.first == order)
            return layer.get();
    }
    std::cout << "Your Scene has no Layer " << order << std::endl;
    exit(-1);
}

auto Scene::getLayer(const std::string& name) -> Layer* {
    for (auto [key, layer] : m_layers) {
        if (key.second == name)
            return layer.get();
    }
    std::cout << "Your Scene has no Layer named " << name << std::endl;
    exit(-1);
}

auto Scene::getDefaultLayer() -> Layer* {
    return m_default_layer.get();
}

void Scene::temporaryLinkCamera(Camera* camera) {
    render_bounds = camera->getGlobalBounds();
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& drawable_variant: m_default_layer->getDrawables()) {
        std::visit([&](auto&& drawable){
           if (render_bounds.intersects(drawable->getGlobalBounds())) {
               target.draw(*drawable, states);
           }
        }, drawable_variant);
        if (std::holds_alternative<ns::DrawableTransformable*>(drawable_variant)) {
            std::get<ns::DrawableTransformable*>(drawable_variant)->changed = false;
        } else if (std::holds_alternative<std::shared_ptr<ns::DrawableTransformable>>(drawable_variant)) {
            std::get<std::shared_ptr<ns::DrawableTransformable>>(drawable_variant)->changed = false;
        }
    }
    for (const auto& [key, layer]: m_layers) {
        for (const auto& drawable_variant: layer->getDrawables()) {
            std::visit([&](auto&& drawable){
                if (render_bounds.intersects(drawable->getGlobalBounds())) {
                    target.draw(*drawable, states);
                }
            }, drawable_variant);
            if (std::holds_alternative<ns::DrawableTransformable*>(drawable_variant)) {
                std::get<ns::DrawableTransformable*>(drawable_variant)->changed = false;
            } else if (std::holds_alternative<std::shared_ptr<ns::DrawableTransformable>>(drawable_variant)) {
                std::get<std::shared_ptr<ns::DrawableTransformable>>(drawable_variant)->changed = false;
            }
        }
    }
}
