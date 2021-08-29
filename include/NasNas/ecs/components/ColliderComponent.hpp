/**
* Created by Modar Nasser on 26/07/2020.
**/

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace ns::ecs  {
    struct ColliderComponentInterface {
        bool dynamic = false;
        virtual auto getBounds() const -> sf::FloatRect = 0;
    };

    struct AABBColliderComponent : ColliderComponentInterface {
        sf::Vector2f position;
        sf::Vector2f size;

        auto getBounds() const -> sf::FloatRect override;
    };

    struct CircleColliderComponent : ColliderComponentInterface {
        sf::Vector2f position;
        float radius;

        auto getBounds() const -> sf::FloatRect override;
    };

    using AABBCollider = AABBColliderComponent;
    using CircleCollider = CircleColliderComponent;
}
