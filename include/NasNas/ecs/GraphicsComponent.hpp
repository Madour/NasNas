/**
* Created by Modar Nasser on 10/06/2020.
**/


#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/ecs/BaseComponent.hpp"
#include "NasNas/data/Rect.hpp"

namespace ns::ecs {

    class GraphicsComponent : public BaseComponent, public sf::Drawable {
    public:
        explicit GraphicsComponent(BaseEntity* entity);
        virtual auto getDrawable() -> sf::Drawable& = 0;
        virtual auto getGlobalBounds() -> ns::FloatRect = 0;
    };

}
