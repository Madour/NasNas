/**
* Created by Modar Nasser on 15/06/2020.
**/


#pragma once

#include <SFML/System.hpp>
#include "NasNas/ecs/BaseComponent.hpp"

namespace ns::ecs {

    class PhysicsComponent : public BaseComponent {
    public:
        PhysicsComponent(BaseEntity* entity, float mass, const sf::Vector2f& max_velocity, const sf::Vector2f& acceleration);
        PhysicsComponent(BaseEntity* entity, float mass, const sf::Vector2f& max_velocity, const sf::Vector2f& acceleration, const sf::Vector2f& friction);

        auto getVelocity() -> sf::Vector2f;
        void setVelocity(const sf::Vector2f& velocity);
        void setVelocity(float velocity_x, float velocity_y);

        auto getDirection() -> sf::Vector2i;
        void setDirection(const sf::Vector2i& direction);
        void setDirection(int direction_x, int direction_y);

        void update() override;

    private:
        float m_mass;
        sf::Vector2i m_direction = {0, 0};
        sf::Vector2f m_velocity = {0, 0};
        sf::Vector2f m_max_velocity;
        sf::Vector2f m_acceleration;
        sf::Vector2f m_friction = {0, 0};
    };

}
