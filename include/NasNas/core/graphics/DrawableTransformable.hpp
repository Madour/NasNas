// Created by Modar Nasser on 20/04/2021.

#pragma once

#include "NasNas/core/graphics/Drawable.hpp"
#include "NasNas/core/graphics/Transformable.hpp"

namespace ns {
    class DrawableTransformable : public ns::Drawable, public ns::Transformable {
    public:
        auto getPosition() const -> sf::Vector2f override {
            return ns::Transformable::getPosition();
        }
    };
}
