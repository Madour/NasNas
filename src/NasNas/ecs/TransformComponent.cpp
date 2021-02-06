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
