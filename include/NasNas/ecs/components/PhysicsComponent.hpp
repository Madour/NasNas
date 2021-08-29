/**
* Created by Modar Nasser on 15/06/2020.
**/


#pragma once

#include <SFML/System.hpp>

namespace ns::ecs {

    class PhysicsComponent {
    public:
        explicit PhysicsComponent(const sf::Vector2f& acceleration, float mass=1.f, const sf::Vector2f& friction={1.f, 1.f});

        auto getMass() const -> float;
        void setMass(float mass);

        auto getVelocity() const -> const sf::Vector2f&;
        void setVelocity(const sf::Vector2f& velocity);
        void setVelocity(float velocity_x, float velocity_y);
        void setVelocityX(float velocity_x);
        void setVelocityY(float velocity_y);

        auto getAcceleration() const -> const sf::Vector2f&;
        void setAcceleration(const sf::Vector2f& acceleration);
        void setAcceleration(float acceleration_x, float acceleration_y);
        void setAccelerationX(float acceleration_x);
        void setAccelerationY(float acceleration_y);

        auto getDirection() const -> const sf::Vector2f&;
        void setDirection(const sf::Vector2f& direction);
        void setDirection(float direction_x, float direction_y);
        void setDirectionX(float direction_x);
        void setDirectionY(float direction_y);

        auto getDirectionAngle() const -> float;
        void setDirectionAngle(float angle);

        auto getDirectionMagnitude() const -> float;
        void setDirectionMagnitude(float magnitude);

        auto getMomentum() const -> sf::Vector2f;

        void update();

    private:
        float m_mass;
        sf::Vector2f m_direction = {0.f, 0.f};
        float m_direction_angle = 0.f;
        float m_direction_magnitude = 1.f;
        sf::Vector2f m_velocity = {0.f, 0.f};
        sf::Vector2f m_acceleration;
        sf::Vector2f m_friction;
    };

    using Physics = PhysicsComponent;

}
