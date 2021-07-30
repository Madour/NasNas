/**
* Created by Modar Nasser on 15/04/2020.
**/

#include <utility>

#include "NasNas/core/Layer.hpp"

using namespace ns;

Layer::Layer(std::string name) : m_name(std::move(name))
{}


void Layer::clear() {
    m_drawables.clear();
    m_gc.clear();
    m_position_getters.clear();
    m_bounds_getters.clear();
}

void Layer::ySort() {
    std::sort(std::begin(m_drawables), std::end(m_drawables),
                [this](auto const lhs, auto const rhs){
                    return m_position_getters[lhs]().y < m_position_getters[rhs]().y;
                }
    );
}

auto Layer::allDrawables() const -> const std::vector<const sf::Drawable*>& {
    return m_drawables;
}

auto Layer::getDrawablePosition(const sf::Drawable* dr) const -> sf::Vector2f {
    if (m_position_getters.find(dr) != m_position_getters.end()) {
        return m_position_getters.at(dr)();
    }
    return {};
}

auto Layer::getDrawableBounds(const sf::Drawable* dr) const -> sf::FloatRect {
    if (m_bounds_getters.find(dr) != m_bounds_getters.end()) {
        return m_bounds_getters.at(dr)();
    }
    return {};
}

auto Layer::getName() const -> const std::string& {
    return m_name;
}



