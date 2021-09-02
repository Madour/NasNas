/**
* Created by Modar Nasser on 15/06/2020.
**/

#include <iostream>

#include "NasNas/ecs/components/PhysicsComponent.hpp"
#include "NasNas/core/data/Maths.hpp"

using namespace ns;
using namespace ns::ecs;

constexpr float FLOAT_ZERO = 0.00001f;

PhysicsComponent::PhysicsComponent(float pmass, const sf::Vector2f& plin_damping, float pang_damping) : mass(pmass) {
    if (plin_damping.x > 1.f || plin_damping.y > 1.f || plin_damping.x < 0.f || plin_damping.y < 0.f) {
        std::cout << "Friction parameter of PhysicsComponentComponent should be a vector between (0, 0) and (1, 1)." << std::endl;
        exit(-1);
    }
    linear_damping = plin_damping;
    angular_damping = std::clamp(pang_damping, 0.f, 1.f);
}

void PhysicsComponent::applyForce(sf::Vector2f force) {
    m_forces += force;
}

void PhysicsComponent::applyTorque(float torque) {
    m_torque += torque;
}

auto PhysicsComponent::getDirection() const -> sf::Vector2f {
    return {std::cos(m_angle), std::sin(m_angle)};
}

auto PhysicsComponent::getAngle() const -> float {
    return ns::to_degree(m_angle);
}

auto PhysicsComponent::getMomentum() const -> sf::Vector2f {
    return mass * linear_velocity;
}

void PhysicsComponent::update() {
    // damping
    linear_velocity.x = (std::abs(linear_velocity.x) <= FLOAT_ZERO) ? 0.f : linear_velocity.x * (1 - linear_damping.x);
    linear_velocity.y = (std::abs(linear_velocity.y) <= FLOAT_ZERO) ? 0.f : linear_velocity.y * (1 - linear_damping.y);
    angular_velocity = (std::abs(angular_velocity) <= FLOAT_ZERO) ? 0.f : angular_velocity * (1 - angular_damping);

    // forces
    linear_velocity += m_forces;
    angular_velocity += m_torque;

    m_angle += angular_velocity;

    m_forces = {0, 0};
    m_torque = 0.f;
}
