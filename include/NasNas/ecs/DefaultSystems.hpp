// Created by Modar Nasser on 29/08/2021.

#pragma once

#include "NasNas/ecs/System.hpp"
#include "NasNas/ecs/components/InputsComponent.hpp"
#include "NasNas/ecs/components/PhysicsComponent.hpp"
#include "NasNas/ecs/components/SpriteComponent.hpp"

namespace ns::ecs {
    extern System<InputsComponent> inputs_system;
    extern System<PhysicsComponent> physics_system;
    extern System<SpriteComponent> sprite_system;
}
