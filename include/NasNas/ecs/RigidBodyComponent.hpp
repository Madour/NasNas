// Created by Modar Nasser on 11/07/2021.

#pragma once

#include "NasNas/ecs/BaseComponent.hpp"

namespace ns::ecs {
    class RigidBodyComponent : public Component<RigidBodyComponent> {
    public:
        float mass = 1;
        float friction = 0;
        float restitution = 1.f;
        sf::Vector2f velocity;
        sf::Vector2f force;
    };

    struct CircleCollider {
        float radius = 0;
    };

    class ColliderGroupComponent : public Component<ColliderGroupComponent> {
        std::vector<std::unique_ptr<CircleCollider>> m_colliders;
    public:
        explicit ColliderGroupComponent(std::unique_ptr<CircleCollider> collider) {
            m_colliders.push_back(std::move(collider));
        }

        auto collider() -> CircleCollider& { return *m_colliders[0]; }
    };
}

