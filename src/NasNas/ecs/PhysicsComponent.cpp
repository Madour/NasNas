/**
* Created by Modar Nasser on 15/06/2020.
**/

#include "NasNas/ecs/BaseEntity.hpp"
#include "NasNas/ecs/PhysicsComponent.hpp"

using namespace ns::ecs;

PhysicsComponent::PhysicsComponent(BaseEntity* entity, float mass, const sf::Vector2f& max_velocity, const sf::Vector2f& acceleration):
BaseComponent(entity) {
    m_entity->m_physics_component = this;
    m_mass = mass;
    m_max_velocity = max_velocity;
    m_acceleration = acceleration;
}

auto PhysicsComponent::getVelocity() -> sf::Vector2f {
    return m_velocity;
}

auto PhysicsComponent::getDirection() -> sf::Vector2i {
    return m_direction;
}

void PhysicsComponent::setDirection(const sf::Vector2i& direction) {
    m_direction = direction;
}

void PhysicsComponent::setDirection(float direction_x, float direction_y) {
    m_direction.x = direction_x;
    m_direction.y = direction_y;
}

void PhysicsComponent::update() {

    switch (m_direction.x) {
        case 1:
            m_velocity.x = (m_velocity.x + m_acceleration.x > m_max_velocity.x) ? m_max_velocity.x : m_velocity.x + m_acceleration.x;
            break;
        case -1:
            m_velocity.x = (m_velocity.x - m_acceleration.x < -m_max_velocity.x) ? -m_max_velocity.x : m_velocity.x - m_acceleration.x;
            break;
        default:
            m_velocity.x *= 0.95f;
    }

    switch (m_direction.y) {
        case 1:
            m_velocity.y = (m_velocity.y + m_acceleration.y > m_max_velocity.y) ? m_max_velocity.y : m_velocity.y + m_acceleration.y;
            break;
        case -1:
            m_velocity.y = (m_velocity.y - m_acceleration.y < -m_max_velocity.y) ? -m_max_velocity.y : m_velocity.y - m_acceleration.y;
            break;
        default:
            m_velocity.y *= 0.95f;
    }

    m_entity->setX(m_entity->getX()  + m_velocity.x);
    m_entity->setY(m_entity->getY()  + m_velocity.y);
}
