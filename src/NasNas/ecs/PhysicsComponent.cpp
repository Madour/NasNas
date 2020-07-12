/**
* Created by Modar Nasser on 15/06/2020.
**/


#include "NasNas/data/Config.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;
using namespace ns::ecs;

PhysicsComponent::PhysicsComponent(BaseEntity* entity, float mass, const sf::Vector2f& max_velocity, const sf::Vector2f& acceleration):
BaseComponent(entity) {
    m_entity->m_physics_component = this;
    m_mass = mass;
    m_max_velocity = max_velocity;
    m_acceleration = acceleration;
}

PhysicsComponent::PhysicsComponent(BaseEntity* entity, float mass, const sf::Vector2f& max_velocity, const sf::Vector2f& acceleration, const sf::Vector2f& friction) :
        PhysicsComponent(entity, mass, max_velocity, acceleration) {
    if (friction.x > 1.0 || friction.y > 1.0) {
        std::cout << "Friction parameter of PhysicsComponent should be a vector between (0, 0) and (1, 1)." << std::endl;
        exit(-1);
    }
    m_friction = friction;
}

auto PhysicsComponent::getVelocity() -> sf::Vector2f {
    return m_velocity;
}

void PhysicsComponent::setVelocity(const sf::Vector2f& velocity) {
    m_velocity = velocity;
}

void PhysicsComponent::setVelocity(float velocity_x, float velocity_y) {
    m_velocity.x = velocity_x;
    m_velocity.y = velocity_y;
}

auto PhysicsComponent::getDirection() -> sf::Vector2i {
    return m_direction;
}

void PhysicsComponent::setDirection(const sf::Vector2i& direction) {
    m_direction = direction;
}

void PhysicsComponent::setDirection(int direction_x, int direction_y) {
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
            m_velocity.x *= 1 - m_friction.x;
    }

    switch (m_direction.y) {
        case 1:
            m_velocity.y = (m_velocity.y + m_acceleration.y > m_max_velocity.y) ? m_max_velocity.y : m_velocity.y + m_acceleration.y;
            break;
        case -1:
            m_velocity.y = (m_velocity.y - m_acceleration.y < -m_max_velocity.y) ? -m_max_velocity.y : m_velocity.y - m_acceleration.y;
            break;
        default:
            m_velocity.y *= 1 - m_friction.y;
    }
    m_velocity.y += m_mass * Config::Physics::gravity;
    m_entity->setX(m_entity->getX()  + m_velocity.x);
    m_entity->setY(m_entity->getY()  + m_velocity.y);
}
