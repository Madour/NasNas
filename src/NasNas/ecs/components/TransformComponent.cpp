// Created by Modar Nasser on 06/02/2021.

#include "NasNas/ecs/components/TransformComponent.hpp"

using namespace ns;
using namespace ns::ecs;

void TransformComponent::setPositionX(float x) {
    setPosition(x, getPosition().y);
}

void TransformComponent::setPositionY(float y) {
    setPosition(getPosition().x, y);
}

void TransformComponent::setScaleX(float x) {
    setScale(x, getScale().y);
}

void TransformComponent::setScaleY(float y) {
    setScale(getScale().x, y);
}
