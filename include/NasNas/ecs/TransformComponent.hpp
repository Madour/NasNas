// Created by Modar Nasser on 06/02/2021.

#pragma once

#include "NasNas/ecs/BaseComponent.hpp"

namespace ns::ecs {

    class TransformComponent : public BaseComponent, public sf::Transformable{
    public:
        static auto getId() -> unsigned long;

        explicit TransformComponent(ComponentGroup* owner);

        void setPositionX(float x);
        void setPositionY(float y);

        void setScaleX(float x);
        void setScaleY(float y);

        void update() override {}

    private:
        static const unsigned long uid;
    };

    typedef TransformComponent Transform;

}
