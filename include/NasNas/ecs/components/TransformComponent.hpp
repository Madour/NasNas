// Created by Modar Nasser on 06/02/2021.

#pragma once

#include <SFML/Graphics/Transformable.hpp>

namespace ns::ecs {

    class TransformComponent : public sf::Transformable {
    public:
        TransformComponent() = default;

        void setPositionX(float x);
        void setPositionY(float y);

        void setScaleX(float x);
        void setScaleY(float y);
    };

    using Transform = TransformComponent;

}
