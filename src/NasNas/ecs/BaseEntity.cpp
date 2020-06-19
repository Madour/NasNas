/**
* Created by Modar Nasser on 15/04/2020.
**/

#include <cmath>
#include "NasNas/ecs/BaseEntity.hpp"
#include "NasNas/ecs/SpriteComponent.hpp"

using namespace ns;

BaseEntity::BaseEntity(const std::string &name) {
    m_name = name;
}

BaseEntity::~BaseEntity() = default;

auto BaseEntity::getPosition() -> sf::Vector2f {
    return sf::Vector2f(getX(), getY());
}
void BaseEntity::setPosition(const sf::Vector2f& pos) {
    setX(pos.x);
    setY(pos.y);
}
void BaseEntity::setPosition(float x, float y) {
    setX(x);
    setY(y);
}

auto BaseEntity::getX() -> float {
    return ((float)m_gx + m_rx) * 16;
}
void BaseEntity::setX(float value) {
    m_gx = (int)value / 16;
    m_rx = (value - (float)m_gx * 16) / 16;
}

auto BaseEntity::getY() -> float {
    return ((float)m_gy + m_ry) * 16;
}
void BaseEntity::setY(float value) {
    m_gy = (int)value / 16;
    m_ry = (value - (float)m_gy * 16) / 16;
}

void BaseEntity::update() {
    if(m_physics_component) physics()->update();
    for (auto& comp: m_components_list) {
        if (comp.get() != m_physics_component) comp->update();
    }
}

void BaseEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto& comp: m_graphics_components_list) {
        target.draw(*comp);
    }
}

auto BaseEntity::physics() -> ecs::PhysicsComponent* {
    if (m_physics_component == nullptr) {
        std::cout << "Entity "+m_name+" does not have a physics component. Please add one first." << std::endl;
        exit(-1);
    }
    return m_physics_component;
}

void BaseEntity::move(float offsetx, float offsety) {
    /*if (std::abs(m_velocity.x) < std::abs(offsetx))
        m_velocity.x = m_acceleration.x * offsetx / std::abs(offsetx) + m_velocity.x;

    if (std::abs(m_velocity.y) < std::abs(offsety))
        m_velocity.y = m_acceleration.y * offsety / std::abs(offsety) + m_velocity.y;*/
}
