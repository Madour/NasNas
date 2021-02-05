/**
* Created by Modar Nasser on 15/06/2020.
**/


#include "NasNas/ecs/PhysicsComponent.hpp"

#include "NasNas/data/Config.hpp"
#include "NasNas/data/Maths.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;
using namespace ns::ecs;

const unsigned long Physics::uid = BaseComponent::getNextId();

auto Physics::getId() -> unsigned long {
    return Physics::uid;
}

Physics::Physics(BaseEntity* entity, const sf::Vector2f& acceleration, float mass, const sf::Vector2f& friction) :
BaseComponent(entity),
m_mass(mass),
m_acceleration(acceleration)
{
    if (friction.x > 1.f || friction.y > 1.f || friction.x < 0.f || friction.y < 0.f) {
        std::cout << "Friction parameter of PhysicsComponent should be a vector between (0, 0) and (1, 1)." << std::endl;
        exit(-1);
    }
    m_friction = friction;
}

auto Physics::getMass() const -> float {
    return m_mass;
}

void Physics::setMass(float mass) {
    m_mass = mass;
}


auto Physics::getVelocity() const -> const sf::Vector2f& {
    return m_velocity;
}

void Physics::setVelocity(const sf::Vector2f& velocity) {
    m_velocity = velocity;
}

void Physics::setVelocity(float velocity_x, float velocity_y) {
    m_velocity.x = velocity_x;
    m_velocity.y = velocity_y;
}

void Physics::setVelocityX(float velocity_x) {
    m_velocity.x = velocity_x;
}

void Physics::setVelocityY(float velocity_y) {
    m_velocity.y = velocity_y;
}


auto Physics::getAcceleration() const -> const sf::Vector2f& {
    return m_acceleration;
}

void Physics::setAcceleration(const sf::Vector2f& acceleration) {
    m_acceleration = acceleration;
}

void Physics::setAcceleration(float acceleration_x, float acceleration_y) {
    m_acceleration.x = acceleration_x;
    m_acceleration.y = acceleration_y;
}

void Physics::setAccelerationX(float acceleration_x) {
    m_acceleration.x = acceleration_x;
}

void Physics::setAccelerationY(float acceleration_y) {
    m_acceleration.y = acceleration_y;
}


auto Physics::getDirection() const -> const sf::Vector2f& {
    return m_direction;
}

void Physics::setDirection(const sf::Vector2f& direction) {
    setDirection(direction.x, direction.y);
}

void Physics::setDirection(float direction_x, float direction_y) {
    m_direction = {std::min(std::max(direction_x, -1.f), 1.f), std::min(std::max(direction_y, -1.f), 1.f)};
    setDirectionAngle(to_degree(std::atan2(m_direction.y, m_direction.x)));
}

void Physics::setDirectionX(float direction_x) {
    setDirection(direction_x, m_direction.y);
}

void Physics::setDirectionY(float direction_y) {
    setDirection(m_direction.x, direction_y);
}

auto Physics::getDirectionAngle() const -> float {
    return m_direction_angle;
}

void Physics::setDirectionAngle(float angle) {
    m_direction_angle = angle;
    if (angle != 0)
        m_direction = {std::cos(to_radian(m_direction_angle)), std::sin(to_radian(m_direction_angle))};
}


auto Physics::getDirectionMagnitude() const -> float {
    return m_direction_magnitude;
}

void Physics::setDirectionMagnitude(float magnitude) {
    m_direction_magnitude = magnitude;
}

auto Physics::getMomentum() const -> sf::Vector2f {
    return m_mass*m_velocity;
}

void Physics::update() {
    // friction
    m_velocity.x = (std::abs(m_velocity.x) > 0.000001f) ? m_velocity.x*(1-m_friction.x) : 0.f;
    m_velocity.y = (std::abs(m_velocity.y) > 0.000001f) ? m_velocity.y*(1-m_friction.y) : 0.f;

    // acceleration
    m_velocity.x += m_acceleration.x*m_direction.x*m_direction_magnitude;
    m_velocity.y += m_acceleration.y*m_direction.y*m_direction_magnitude;

    // gravity
    m_velocity.y += m_mass * Config::Physics::gravity;

    // position
    m_entity->transform()->move(m_velocity);
}
