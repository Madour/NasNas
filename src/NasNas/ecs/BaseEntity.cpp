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

auto BaseEntity::getGlobalBounds() -> ns::FloatRect {
    float left, top, right, bottom;
    ns::FloatRect result;
    bool first = true;
    for (const auto& graphic_comp : m_graphics_components_list) {
        if (first) {
            left = graphic_comp->getGlobalBounds().left;
            top = graphic_comp->getGlobalBounds().top;
            right = graphic_comp->getGlobalBounds().right();
            bottom = graphic_comp->getGlobalBounds().bottom();
            first = false;
        }
        else {
            left = std::min(left, graphic_comp->getGlobalBounds().left);
            top = std::min(top, graphic_comp->getGlobalBounds().top);
            right = std::max(right, graphic_comp->getGlobalBounds().right());
            bottom = std::max(bottom, graphic_comp->getGlobalBounds().bottom());
        }
    }
    if (!first)
        result = ns::FloatRect(left, top, right - left, bottom - top);
    else
        result = ns::FloatRect(0, 0, 0, 0);

    return result;
}

void BaseEntity::move(float offsetx, float offsety) {
    setX(getX() + offsetx);
    setY(getY() + offsety);
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
    for (const auto& comp: m_graphics_components_list) {
        target.draw(*comp, states);
    }
    if (Config::debug) {
        if (m_collider_component)
            target.draw(m_collider_component->getCollision().getShape());
    }

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
