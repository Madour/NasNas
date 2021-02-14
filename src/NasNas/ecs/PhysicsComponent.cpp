/**
* Created by Modar Nasser on 15/06/2020.
**/


#include "NasNas/ecs/PhysicsComponent.hpp"

#include "NasNas/core/data/Config.hpp"
#include "NasNas/core/data/Maths.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;
using namespace ns::ecs;

PhysicsComponent::PhysicsComponent(const sf::Vector2f& acceleration, float mass, const sf::Vector2f& friction) :
m_mass(mass),
m_acceleration(acceleration)
{
    if (friction.x > 1.f || friction.y > 1.f || friction.x < 0.f || friction.y < 0.f) {
        std::cout << "Friction parameter of PhysicsComponentComponent should be a vector between (0, 0) and (1, 1)." << std::endl;
        exit(-1);
    }
    m_friction = friction;
}

auto PhysicsComponent::getMass() const -> float {
    return m_mass;
}

void PhysicsComponent::setMass(float mass) {
    m_mass = mass;
}


auto PhysicsComponent::getVelocity() const -> const sf::Vector2f& {
    return m_velocity;
}

void PhysicsComponent::setVelocity(const sf::Vector2f& velocity) {
    m_velocity = velocity;
}

void PhysicsComponent::setVelocity(float velocity_x, float velocity_y) {
    m_velocity.x = velocity_x;
    m_velocity.y = velocity_y;
}

void PhysicsComponent::setVelocityX(float velocity_x) {
    m_velocity.x = velocity_x;
}

void PhysicsComponent::setVelocityY(float velocity_y) {
    m_velocity.y = velocity_y;
}


auto PhysicsComponent::getAcceleration() const -> const sf::Vector2f& {
    return m_acceleration;
}

void PhysicsComponent::setAcceleration(const sf::Vector2f& acceleration) {
    m_acceleration = acceleration;
}

void PhysicsComponent::setAcceleration(float acceleration_x, float acceleration_y) {
    m_acceleration.x = acceleration_x;
    m_acceleration.y = acceleration_y;
}

void PhysicsComponent::setAccelerationX(float acceleration_x) {
    m_acceleration.x = acceleration_x;
}

void PhysicsComponent::setAccelerationY(float acceleration_y) {
    m_acceleration.y = acceleration_y;
}


auto PhysicsComponent::getDirection() const -> const sf::Vector2f& {
    return m_direction;
}

void PhysicsComponent::setDirection(const sf::Vector2f& direction) {
    setDirection(direction.x, direction.y);
}

void PhysicsComponent::setDirection(float direction_x, float direction_y) {
    m_direction = {std::min(std::max(direction_x, -1.f), 1.f), std::min(std::max(direction_y, -1.f), 1.f)};
    setDirectionAngle(to_degree(std::atan2(m_direction.y, m_direction.x)));
}

void PhysicsComponent::setDirectionX(float direction_x) {
    setDirection(direction_x, m_direction.y);
}

void PhysicsComponent::setDirectionY(float direction_y) {
    setDirection(m_direction.x, direction_y);
}

auto PhysicsComponent::getDirectionAngle() const -> float {
    return m_direction_angle;
}

void PhysicsComponent::setDirectionAngle(float angle) {
    m_direction_angle = angle;
    if (angle != 0)
        m_direction = {std::cos(to_radian(m_direction_angle)), std::sin(to_radian(m_direction_angle))};
}


auto PhysicsComponent::getDirectionMagnitude() const -> float {
    return m_direction_magnitude;
}

void PhysicsComponent::setDirectionMagnitude(float magnitude) {
    m_direction_magnitude = magnitude;
}

auto PhysicsComponent::getMomentum() const -> sf::Vector2f {
    return m_mass*m_velocity;
}

void PhysicsComponent::update() {
    // friction
    m_velocity.x = (std::abs(m_velocity.x) > 0.000001f) ? m_velocity.x*(1-m_friction.x) : 0.f;
    m_velocity.y = (std::abs(m_velocity.y) > 0.000001f) ? m_velocity.y*(1-m_friction.y) : 0.f;

    // acceleration
    m_velocity.x += m_acceleration.x*m_direction.x*m_direction_magnitude;
    m_velocity.y += m_acceleration.y*m_direction.y*m_direction_magnitude;

    // gravity
    m_velocity.y += m_mass * Config::Physics::gravity;

    // position
    m_owner->get<Transform>()->move(m_velocity);
}
