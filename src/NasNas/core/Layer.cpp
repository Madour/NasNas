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

void Layer::add(const ns::Drawable& drawable) {
    m_drawables.emplace_back(&drawable);
}
void Layer::add(const ns::DrawableTransformable& drawable) {
    m_drawables.emplace_back(&drawable);
}
void Layer::add(const sf::Shape& drawable) {
    m_drawables.emplace_back(&drawable);
}
void Layer::add(const sf::Text& drawable) {
    m_drawables.emplace_back(&drawable);
}
void Layer::add(const sf::Sprite& drawable) {
    m_drawables.emplace_back(&drawable);
}
void Layer::add(const DrawablesTypes& drawable) {
    m_drawables.push_back(drawable);
    if (std::holds_alternative<const ns::Drawable*>(drawable)) {
        m_gc.emplace_back(std::shared_ptr<const Drawable>(std::get<const ns::Drawable*>(drawable)));
    }
    else if (std::holds_alternative<const ns::DrawableTransformable*>(drawable)) {
        m_gc.emplace_back(std::shared_ptr<const DrawableTransformable>(std::get<const ns::DrawableTransformable*>(drawable)));
    }
    else if (std::holds_alternative<const sf::Shape*>(drawable)) {
        m_gc.emplace_back(std::shared_ptr<const sf::Shape>(std::get<const sf::Shape*>(drawable)));
    }
    else if (std::holds_alternative<const sf::Text*>(drawable)) {
        m_gc.emplace_back(std::shared_ptr<const sf::Text>(std::get<const sf::Text*>(drawable)));
    }
    else if (std::holds_alternative<const sf::Sprite*>(drawable)) {
        m_gc.emplace_back(std::shared_ptr<const sf::Sprite>(std::get<const sf::Sprite*>(drawable)));
    }
}

void Layer::addRaw(const DrawablesTypes& drawable) {
    m_drawables.push_back(drawable);
}

void Layer::remove(const ns::Drawable& drawable) {
    remove(&drawable);
}
void Layer::remove(const ns::DrawableTransformable& drawable) {
    remove(&drawable);
}
void Layer::remove(const sf::Shape& drawable) {
    remove(&drawable);
}
void Layer::remove(const sf::Text& drawable) {
    remove(&drawable);
}
void Layer::remove(const sf::Sprite& drawable) {
    remove(&drawable);
}
void Layer::remove(const DrawablesTypes& drawable) {
    auto it = std::find(m_drawables.begin(), m_drawables.end(), drawable);
    if (it != m_drawables.end())
        m_drawables.erase(it);
    else
        std::cout << "Warning : trying to remove a non existant drawable (type index "
                  << drawable.index() << ") from Layer " << m_name << ".\n";
    m_gc.erase(std::remove_if(m_gc.begin(), m_gc.end(), [&](auto& sptr){
        return std::visit([&](auto& x){
            return std::visit([&](auto& d){ return (void*)x.get() == (void*)d; }, drawable);
        }, sptr);
    }), m_gc.end());
}

void Layer::ySort() {
    std::sort(std::begin(m_drawables), std::end(m_drawables),
              [](auto const& lhs, auto const& rhs){
            return std::visit([](auto const& s) { return s->getPosition().y; }, lhs)
                   < std::visit([](auto const& s) { return s->getPosition().y; }, rhs);
        }
    );
}

auto Layer::getName() const -> const std::string& {
    return m_name;
}

auto Layer::getDrawables() const -> const std::vector<DrawablesTypes>& {
    return m_drawables;
}
