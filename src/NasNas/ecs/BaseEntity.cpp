/**
* Created by Modar Nasser on 15/04/2020.
**/


#include <cmath>
#include "NasNas/data/Config.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;

BaseEntity::BaseEntity(const std::string& name) {
    m_name = name;
}

BaseEntity::~BaseEntity() = default;

auto BaseEntity::getPosition() -> sf::Vector2f {
    return m_transformable.getPosition();
}

void BaseEntity::setX(float value) {
    m_gx = (int)value / 16;
    m_rx = (value - (float)m_gx * 16) / 16;
    m_transformable.setPosition(value, m_transformable.getPosition().y);
}

void BaseEntity::setY(float value) {
    m_gy = (int)value / 16;
    m_ry = (value - (float)m_gy * 16) / 16;
    m_transformable.setPosition(m_transformable.getPosition().x, value);
}

auto BaseEntity::getGlobalBounds() -> ns::FloatRect {
    float left, top, right, bottom;
    ns::FloatRect result;
    bool first = true;
    for (const auto& graphic_comp : m_graphics_components_list) {
        auto topleft = transform()->getTransform().transformPoint(graphic_comp->getGlobalBounds().topleft());
        auto bottomright = transform()->getTransform().transformPoint(graphic_comp->getGlobalBounds().bottomright());
        if (first) {
            left = topleft.x;
            top = topleft.y;
            right = bottomright.x;
            bottom = bottomright.y;
            first = false;
        }
        else {
            left = std::min(left, topleft.x);
            top = std::min(top, topleft.y);
            right = std::max(right, bottomright.x);
            bottom = std::max(bottom, bottomright.y);
        }
    }
    if (!first)
        result = ns::FloatRect(left, top, right - left, bottom - top);
    else
        result = ns::FloatRect(0, 0, 0, 0);

    return result;
}

void BaseEntity::update() {
    if(m_inputs_component) m_inputs_component->update();
    if(m_physics_component) m_physics_component->update();
    if(m_collider_component) m_collider_component->update();
    for (const auto& graphic_comp: m_graphics_components_list) {
        graphic_comp->update();
    }
}

void BaseEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= m_transformable.getTransform();
    for (const auto& comp: m_graphics_components_list) {
        target.draw(*comp, states);
    }
    if (Config::debug) {
        if (m_collider_component)
            target.draw(m_collider_component->getCollision().getShape());
    }

}

auto BaseEntity::transform() -> sf::Transformable* {
    return &m_transformable;
}

auto BaseEntity::inputs() -> ecs::InputsComponent* {
    if(m_inputs_component) {
        return m_inputs_component;
    }
    std::cout << "Entity «"+m_name+"» does not have a InputsComponent. Please add one first." << std::endl;
    exit(-1);
}

auto BaseEntity::physics() -> ecs::PhysicsComponent* {
    if (m_physics_component) {
        return m_physics_component;
    }
    std::cout << "Entity «"+m_name+"» does not have a PhysicsComponent. Please add one first." << std::endl;
    exit(-1);
}

auto BaseEntity::graphics() -> std::vector<ecs::GraphicsComponent*>& {
    return m_graphics_components_list;
}

auto BaseEntity::collider() -> ecs::ColliderComponent* {
    return m_collider_component;
}
