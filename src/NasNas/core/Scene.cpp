/**
* Created by Modar Nasser on 19/04/2020.
**/

#include "NasNas/core/Scene.hpp"

using namespace ns;


Scene::Scene(int width, int height) {
    this->render_texture.create(width, height);
    this->sprite.setTexture(this->render_texture.getTexture());
}

void Scene::addLayer(const std::shared_ptr<Layer>& layer, int order) {
    this->layers[order] = std::make_shared<Layer>(*layer);
}

void Scene::addLayer(std::shared_ptr<Layer>& layer, int order) {
    this->layers[order] = layer;

}


auto Scene::getLayer(int order) -> Layer* {
    return this->layers.at(order).get();
}

auto Scene::getWidth() -> int { return this->render_texture.getSize().x;}
auto Scene::getHeight() -> int { return this->render_texture.getSize().y;}

void Scene::render() {
    this->render_texture.clear(this->clear_color);
    for (auto& item: this->layers) {
        this->render_texture.draw(*item.second);
    }
    this->render_texture.display();
    this->sprite.setTexture(this->render_texture.getTexture());
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}




