// Created by Modar Nasser on 11/07/2021.

#pragma once

#include "NasNas/ecs/BaseComponent.hpp"
#include "NasNas/ecs/TransformComponent.hpp"

namespace ns::ecs {
    class RigidBodyComponent : public Component<RigidBodyComponent> {
    public:
        float mass = 1;
        float friction = 0;
        float restitution = 1.f;
        sf::Vector2f velocity;
        sf::Vector2f force;
    };


    struct Manifold {
        sf::Vector2f A;
        sf::Vector2f B;
        sf::Vector2f normal;
        float depth = 0.f;
    };
    struct CircleCollider;
    struct RectangleCollider;

    auto findManifold(CircleCollider* a, TransformComponent* ta, CircleCollider* b, TransformComponent* tb) -> Manifold ;

    struct BodyCollider {
        virtual auto testCollision(TransformComponent* tr, BodyCollider* collider, TransformComponent* collider_tr) -> Manifold = 0;
        virtual auto testCollision(TransformComponent* tr, CircleCollider* collider, TransformComponent* collider_tr) -> Manifold = 0;
        //virtual auto testCollision(TransformComponent* tr, RectangleCollider* collider, TransformComponent* collider_tr) -> Manifold = 0;
    };

    struct CircleCollider : BodyCollider {
        float radius = 0;
        auto testCollision(TransformComponent* tr, BodyCollider* other, TransformComponent* other_tr) -> Manifold override;
        auto testCollision(TransformComponent* tr, CircleCollider* other, TransformComponent* other_tr) -> Manifold override;
        //auto testCollision(TransformComponent* tr, RectangleCollider* other, TransformComponent* other_tr) -> Manifold override;
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

