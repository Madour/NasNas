// Created by Modar Nasser on 15/06/2020.

#pragma once

#include <SFML/System/Vector2.hpp>

namespace ns::ecs {

    class PhysicsComponent {
    public:
        explicit PhysicsComponent(float mass=1.f, const sf::Vector2f& linear_damping={1.f, 1.f}, float angular_damping=1.f);

        float mass = 1.f;

        sf::Vector2f linear_velocity = {0.f, 0.f};
        sf::Vector2f linear_damping = {1.f, 1.f};

        float angular_velocity = 0.f;
        float angular_damping = 1.f;

        void applyForce(sf::Vector2f force);
        void applyTorque(float torque);

        auto getDirection() const -> sf::Vector2f;
        auto getAngle() const -> float;

        auto getMomentum() const -> sf::Vector2f;

        void update();

    private:
        sf::Vector2f m_forces;
        float m_torque = 0.f;
        float m_angle = 0.f;
    };

    using Physics = PhysicsComponent;

}
