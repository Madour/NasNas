/**
* Created by Modar Nasser on 10/06/2020.
**/


#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/ecs/BaseComponent.hpp"
#include "NasNas/data/Rect.hpp"

namespace ns::ecs {

    class GraphicsComponent : public sf::Drawable {
    public:
        ~GraphicsComponent() override = default;
        virtual auto getDrawable() -> sf::Drawable& = 0;
        virtual auto getGlobalBounds() -> ns::FloatRect = 0;
        virtual void update() = 0;

    protected:
        sf::Transform m_transform;
    };

    typedef GraphicsComponent Graphics;
}
