// Created by Modar Nasser on 29/08/2021.

#include <NasNas/ecs/DefaultSystems.hpp>

ns::ecs::System<ns::ecs::InputsComponent> ns::ecs::inputs_system{[](auto& inputs) { inputs.update(); }};
ns::ecs::System<ns::ecs::PhysicsComponent> ns::ecs::physics_system{[](auto& physics) {physics.update();}};
ns::ecs::System<ns::ecs::SpriteComponent> ns::ecs::sprite_system{[](auto& sprite) { sprite.update(); }};
