/**
* Created by Modar Nasser on 26/07/2020.
**/

#pragma once

#include <SFML/System/Vector2.hpp>
#include <NasNas/core/data/Rect.hpp>

namespace ns::ecs  {
    struct ColliderComponentInterface {
        bool dynamic = false;
        virtual auto getBounds() const -> ns::FloatRect = 0;
    };

    struct AABBColliderComponent : ColliderComponentInterface {
        sf::Vector2f position;
        sf::Vector2f size;

        auto getBounds() const -> ns::FloatRect override;
    };

    struct CircleColliderComponent : ColliderComponentInterface {
        sf::Vector2f position;
        float radius;

        auto getBounds() const -> ns::FloatRect override;
    };

    using AABBCollider = AABBColliderComponent;
    using CircleCollider = CircleColliderComponent;
}
