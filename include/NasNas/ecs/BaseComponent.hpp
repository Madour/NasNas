/**
* Created by Modar Nasser on 09/06/2020.
**/


#pragma once

#include "NasNas/data/Shapes.hpp"

namespace ns {
    class BaseEntity;
}

namespace ns::ecs {
    class PhysicsComponent;
    class SpriteComponent;
    class InputsComponent;
    class ColliderComponent;
    template <class T>
    class ShapeComponent;

    class BaseComponent {
    public:
        explicit BaseComponent(BaseEntity* entity);
        virtual ~BaseComponent() = default;
        virtual void update() = 0;

    protected:
        BaseEntity* m_entity;

    private:
        friend BaseEntity;
        friend PhysicsComponent;
        friend InputsComponent;
        friend ColliderComponent;
        friend SpriteComponent;
        friend ShapeComponent<sf::CircleShape>;
        friend ShapeComponent<ns::EllipseShape>;
        friend ShapeComponent<ns::LineShape>;
        friend ShapeComponent<sf::RectangleShape>;
        friend ShapeComponent<sf::ConvexShape>;

        static auto getNextId() -> unsigned long;
        static unsigned long id_counter;

    };

}
