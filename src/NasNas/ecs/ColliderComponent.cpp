/**
* Created by Modar Nasser on 26/07/2020.
**/


#include "NasNas/data/Maths.hpp"
#include "NasNas/ecs/ColliderComponent.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;
using namespace ns::ecs;

template <>
auto ns::ecs::checkCollision(RectangleCollision& col1, RectangleCollision& col2) -> bool {
    return col1.getShape().getGlobalBounds().intersects(col2.getShape().getGlobalBounds());
}

template <>
auto ns::ecs::checkCollision(RectangleCollision& col1, CircleCollision& col2) -> bool {
    auto& rect = *dynamic_cast<sf::RectangleShape*>(&col1.getShape());
    auto& circle = *dynamic_cast<sf::CircleShape*>(&col2.getShape());
    for (unsigned int i=0; i < rect.getPointCount(); i++) {

        auto vec = rect.getTransform().transformPoint(rect.getPoint(i)) -
               (circle.getPosition() - circle.getOrigin() + sf::Vector2f(col2.getRadius(), col2.getRadius()));

        if (ns::norm(vec) < col2.getRadius())
            return true;
    }
    return false;
}

template <>
auto ns::ecs::checkCollision(CircleCollision& col1, CircleCollision& col2) -> bool {
    auto pos1 = col1.getShape().getPosition() - col1.getShape().getOrigin();
    auto pos2 = col2.getShape().getPosition() - col2.getShape().getOrigin();
    auto total_radius = col1.getRadius() + col2.getRadius();
    return std::abs(ns::norm(pos2 - pos1)) <= total_radius;
}

Collision::Collision(CollisionType col_type) :
type(col_type) {
    m_dummy_shape.setRadius(0);
}

auto Collision::collide(Collision& other) -> bool {
    if (type == CollisionType::Rectangle && other.type == CollisionType::Rectangle) {
        return checkCollision(
                *dynamic_cast<RectangleCollision*>(this),
                *dynamic_cast<RectangleCollision*>(&other)
        );
    }
    else if (type == CollisionType::Rectangle && other.type == CollisionType::Circle) {
        return checkCollision(
                *dynamic_cast<RectangleCollision*>(this),
                *dynamic_cast<CircleCollision*>(&other)
        );
    }
    else if (type == CollisionType::Circle && other.type == CollisionType::Rectangle) {
        return checkCollision(
                *dynamic_cast<RectangleCollision*>(&other),
                *dynamic_cast<CircleCollision*>(this)
        );
    }
    else if (type == CollisionType::Circle && other.type == CollisionType::Circle) {
        return checkCollision(
                *dynamic_cast<CircleCollision*>(this),
                *dynamic_cast<CircleCollision*>(&other)
        );
    }

    return false;
}


auto Collision::getShape() -> sf::Shape& {
    return m_dummy_shape;
}

auto Collision::getWidth() -> float { return 0; }
auto Collision::getHeight() -> float { return 0; }
auto Collision::getRadius() -> float { return 0; }


RectangleCollision::RectangleCollision(float width, float height) :
Collision(CollisionType::Rectangle) {
    m_shape.setSize({width, height});
    m_shape.setOrigin(width/2, height/2);
    m_shape.setFillColor(sf::Color(255, 0, 0, 120));
}
auto RectangleCollision::getShape() -> sf::Shape& {
    return m_shape;
}
auto RectangleCollision::getWidth() -> float { return m_shape.getSize().x; }
auto RectangleCollision::getHeight() -> float { return m_shape.getSize().y; }


CircleCollision::CircleCollision(float radius) :
Collision(CollisionType::Circle) {
    m_shape.setRadius(radius);
    m_shape.setOrigin(radius, radius);
    m_shape.setFillColor(sf::Color(255, 0, 0, 120));
}
auto CircleCollision::getShape() -> sf::Shape& {
    return m_shape;
}
auto CircleCollision::getRadius() -> float { return m_shape.getRadius(); }


ColliderComponent::ColliderComponent(BaseEntity* entity, Collision* collision, sf::Vector2f pos_offset) :
BaseComponent(entity),
m_collision_box(collision),
m_pos_offset(pos_offset) {
    m_entity->m_collider_component = this;
    m_collision_box->getShape().setPosition(m_entity->getPosition() + m_pos_offset);
}

ColliderComponent::~ColliderComponent() {
    switch (m_collision_box->type) {
        case Collision::CollisionType::Rectangle:
            delete(dynamic_cast<RectangleCollision*>(m_collision_box));
            break;
        case Collision::CollisionType::Circle:
            delete(dynamic_cast<CircleCollision*>(m_collision_box));
            break;
        default:
            delete(m_collision_box);
            break;
    }
}

auto ColliderComponent::isDynamic() const -> bool {
    return m_entity->physics() != nullptr;
}

auto ColliderComponent::getCollision() -> Collision& {
    return *m_collision_box;
}

void ColliderComponent::update() {
    m_collision_box->getShape().setPosition(m_entity->getPosition() + m_pos_offset);
}
