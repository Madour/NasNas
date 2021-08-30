/**
* Created by Modar Nasser on 26/07/2020.
**/

#include "NasNas/ecs/components/ColliderComponent.hpp"

using namespace ns::ecs;

auto AABBColliderComponent::getBounds() const -> ns::FloatRect {
    return {position-size/2.f, size};
}

auto CircleColliderComponent::getBounds() const -> ns::FloatRect {
    sf::Vector2f size{radius, radius};
    return {position-size/2.f, size};
}
