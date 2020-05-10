/**
* Created by Modar Nasser on 15/04/2020.
**/

#include <variant>
#include <vector>
#include "NasNas/core/Layers.hpp"

using namespace ns;

Layer::Layer(const std::string &name) {
    this->name = name;
}

void Layer::add(const std::shared_ptr<sf::Shape>& drawable) {
    this->drawables.emplace_back(drawable);
}

void Layer::add(const std::shared_ptr<sf::Text>& drawable) {
    this->drawables.emplace_back(drawable);
}

void Layer::add(const std::shared_ptr<ns::Drawable>& drawable) {
    this->drawables.emplace_back(drawable);
}

void Layer::ySort() {
    std::sort(std::begin(this->drawables),std::end(this->drawables),
        [](auto const& lhs, auto const& rhs){
            return std::visit([](auto const& s) { return s->getPosition().y; }, lhs)
                   < std::visit([](auto const& s) { return s->getPosition().y; }, rhs);
        }
    );
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const DrawablesTypes& drawable: this->drawables) {
        std::visit([&](auto&& arg){target.draw(*arg);}, drawable);
    }
}

auto Layer::getName() -> std::string& {
    return this->name;
}

auto Layer::getDrawables() -> std::vector<DrawablesTypes> & {
    return this->drawables;
}


