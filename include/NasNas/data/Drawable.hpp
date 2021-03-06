/**
* Created by Modar Nasser on 12/07/2020.
**/


#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/data/Rect.hpp"

namespace ns {

    /** Drawable is an interface for any object
     * that can be drawn on a RenderTarget
     */
    class Drawable : public sf::Drawable {
    public:
        virtual auto getPosition() const -> sf::Vector2f = 0;
        virtual auto getGlobalBounds() const -> ns::FloatRect = 0;
    };

    class DrawableTransformable : public ns::Drawable, public sf::Transformable {
    public:
        auto getPosition() const -> sf::Vector2f override {
            return sf::Transformable::getPosition();
        }
    };

}
