/**
* Created by Modar Nasser on 26/07/2020.
**/


#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/ecs/BaseComponent.hpp"

namespace ns::ecs  {

    class Collision {

    protected:
        enum class CollisionType {
            Rectangle,
            Circle
        };

    public:
        explicit Collision(CollisionType col_type);
        virtual ~Collision() = default;

        auto collide(Collision& other) -> bool;

        virtual auto getShape() -> sf::Shape&;

        const CollisionType type;

    protected:
        friend ColliderComponent;
        virtual auto getWidth() -> float;
        virtual auto getHeight() -> float;
        virtual auto getRadius() -> float;

    private:
        sf::CircleShape m_dummy_shape;

    };


    class RectangleCollision : public Collision {
    public:
        RectangleCollision(float width, float height);

        auto getWidth() -> float override;
        auto getHeight() -> float override;

        auto getShape() -> sf::Shape& override;

    private:
        sf::RectangleShape m_shape;
    };

    class CircleCollision : public Collision {
    public:
        explicit CircleCollision(float radius);

        auto getRadius() -> float override;

        auto getShape() -> sf::Shape& override;

    private:
        sf::CircleShape m_shape;
    };


    class ColliderComponent : public BaseComponent {
    public:
        static auto getId() -> unsigned long;

        explicit ColliderComponent(ComponentGroup* owner, Collision* collision, sf::Vector2f pos_offset={0, 0});
        ~ColliderComponent() override;

        auto isDynamic() const -> bool;

        auto getCollision() -> Collision&;

        void update() override;

    private:
        static const unsigned long uid;

        sf::Vector2f m_pos_offset;
        Collision* m_collision_box;

    };

    typedef ColliderComponent Collider;

    template <typename T, typename S>
    auto checkCollision(T& col1, S& col2) -> bool;

}
