// Created by Modar Nasser on 06/02/2021.

#include "NasNas/ecs/TransformComponent.hpp"

using namespace ns;
using namespace ns::ecs;

const unsigned long TransformComponent::uid = BaseComponent::getNextId();

auto TransformComponent::getId() -> unsigned long {
    return TransformComponent::uid;
}

TransformComponent::TransformComponent(ComponentGroup* owner) :
BaseComponent(owner)
{}


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
