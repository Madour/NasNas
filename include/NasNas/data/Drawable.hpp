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
        virtual auto getPosition() -> sf::Vector2f = 0;
        virtual auto getGlobalBounds() -> ns::FloatRect = 0;
    };

}
