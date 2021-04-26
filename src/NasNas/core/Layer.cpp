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
}

void Layer::add(const DrawablesSharedTypes& drawable) {
    m_drawables.push_back(std::visit([](auto const& d) -> DrawablesTypes { return d; }, drawable));
}

void Layer::add(const DrawablesRawTypes& drawable) {
    if (std::holds_alternative<ns::Drawable*>(drawable)) {
        m_drawables.emplace_back(std::shared_ptr<ns::Drawable>(std::get<ns::Drawable*>(drawable)));
    }
    else if (std::holds_alternative<ns::DrawableTransformable*>(drawable)) {
        m_drawables.emplace_back(std::shared_ptr<ns::DrawableTransformable>(std::get<ns::DrawableTransformable*>(drawable)));
    }
    else if (std::holds_alternative<sf::Shape*>(drawable)) {
        m_drawables.emplace_back(std::shared_ptr<sf::Shape>(std::get<sf::Shape*>(drawable)));
    }
    else if (std::holds_alternative<sf::Text*>(drawable)) {
        m_drawables.emplace_back(std::shared_ptr<sf::Text>(std::get<sf::Text*>(drawable)));
    }
    else if (std::holds_alternative<sf::Sprite*>(drawable)) {
        m_drawables.emplace_back(std::shared_ptr<sf::Sprite>(std::get<sf::Sprite*>(drawable)));
    }
}

void Layer::addRaw(const DrawablesRawTypes& drawable) {
    m_drawables.push_back(std::visit([](auto const& d) -> DrawablesTypes { return d; }, drawable));
}

void Layer::remove(const DrawablesTypes& drawable) {
    auto it = std::find(m_drawables.begin(), m_drawables.end(), drawable);
    if (it != m_drawables.end())
        m_drawables.erase(it);
    else
        std::cout << "Warning : trying to remove a non existant drawable (type index "
                  << drawable.index() << ") from Layer " << m_name << ".\n";
}

void Layer::ySort() {
    std::sort(std::begin(m_drawables), std::end(m_drawables),
              [](auto const& lhs, auto const& rhs){
            return std::visit([](auto const& s) { return s->getPosition().y; }, lhs)
                   <std::visit([](auto const& s) { return s->getPosition().y; }, rhs);
        }
    );
}

auto Layer::getName() const -> const std::string& {
    return m_name;
}

auto Layer::getDrawables() const -> const std::vector<DrawablesTypes>& {
    return m_drawables;
}
