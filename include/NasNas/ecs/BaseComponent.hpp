/**
* Created by Modar Nasser on 09/06/2020.
**/


#pragma once

#include "NasNas/data/Shapes.hpp"

namespace ns {
    class BaseEntity;
}

namespace ns::ecs {
    class Physics;
    class Sprite;
    class Inputs;
    class Collider;
    template <class T>
    class Shape;

    class BaseComponent {
    public:
        explicit BaseComponent(BaseEntity* entity);
        virtual ~BaseComponent() = default;
        virtual void update() = 0;

    protected:
        BaseEntity* m_entity;

    private:
        friend BaseEntity;
        friend Physics;
        friend Inputs;
        friend Collider;
        friend Sprite;
        friend Shape<sf::CircleShape>;
        friend Shape<ns::EllipseShape>;
        friend Shape<ns::LineShape>;
        friend Shape<sf::RectangleShape>;
        friend Shape<sf::ConvexShape>;

        static auto getNextId() -> unsigned long;
        static unsigned long id_counter;

    };

}
