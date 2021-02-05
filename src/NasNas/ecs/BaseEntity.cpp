/**
* Created by Modar Nasser on 15/04/2020.
**/


#include <cmath>
#include "NasNas/data/Config.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;

BaseEntity::BaseEntity(std::string name) :
m_name(std::move(name))
{
    m_components.resize(ecs::BaseComponent::id_counter, nullptr);
}

BaseEntity::~BaseEntity() {
    for (auto* comp : m_components)
        delete comp;
}

auto BaseEntity::getPosition() const -> sf::Vector2f {
    return m_transformable.getPosition();
}

void BaseEntity::setX(float value) {
    m_transformable.setPosition(value, m_transformable.getPosition().y);
}

void BaseEntity::setY(float value) {
    m_transformable.setPosition(m_transformable.getPosition().x, value);
}

auto BaseEntity::getGlobalBounds() const -> ns::FloatRect {
    float left, top, right, bottom;
    ns::FloatRect result{0, 0, 0, 0};
    bool first = true;
    for (const auto& graphic_comp : m_graphics) {
        auto rect = graphic_comp->getGlobalBounds();
        auto topleft = rect.topleft();
        auto topright = rect.topright();
        auto bottomleft = rect.bottomleft();
        auto bottomright = rect.bottomright();
        if (first) {
            left = std::min(topleft.x, bottomleft.x);
            top = std::min(topleft.y, topright.y);
            right = std::max(topright.x, bottomright.x);
            bottom = std::max(bottomleft.y, bottomright.y);
            first = false;
        } else {
            left = std::min(left, std::min(topleft.x, bottomleft.x));
            top = std::min(top, std::min(topleft.y, topright.y));
            right = std::max(right, std::max(topright.x, bottomright.x));
            bottom = std::max(bottom, std::max(bottomleft.y, bottomright.y));
        }
    }
    if (!first) {
        result.left = left;
        result.top = top;
        result.width = right - left;
        result.height = bottom - top;
    }
    return result;
}

void BaseEntity::update() {
    get<ns::ecs::Inputs>()->update();
    get<ns::ecs::Physics>()->update();
    get<ns::ecs::Collider>()->update();
    for (auto* comp : m_graphics)
        comp->update();
}

void BaseEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= m_transformable.getTransform();

    for (const auto& comp: m_graphics) {
        target.draw(*comp, states);
    }
    if (Config::debug) {
        if (collider())
            target.draw(collider()->getCollision().getShape());
    }

}

auto BaseEntity::transform() -> sf::Transformable* {
    return &m_transformable;
}

auto BaseEntity::inputs() const -> ecs::Inputs* {
    return get<ecs::Inputs>();
}

auto BaseEntity::physics() const -> ecs::Physics* {
    return get<ecs::Physics>();
}

auto BaseEntity::collider() const -> ecs::Collider* {
    return get<ecs::Collider>();
}

auto BaseEntity::graphics() -> std::vector<ecs::GraphicsComponent*>& {
    return m_graphics;
}
