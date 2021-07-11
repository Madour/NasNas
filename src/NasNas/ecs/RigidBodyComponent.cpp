// Created by Modar Nasser on 11/07/2021.

#include "NasNas/ecs/RigidBodyComponent.hpp"

using namespace ns;
using namespace ns::ecs;

auto ns::ecs::findManifold(CircleCollider* a, TransformComponent* ta, CircleCollider* b, TransformComponent* tb) -> Manifold {
    auto normal = tb->getPosition() - ta->getPosition();
    auto depth = a->radius + b->radius - ns::norm(normal);
    auto u_normal = normal / ns::norm(normal);
    auto A = ta->getPosition() + u_normal * (a->radius - depth);
    auto B = tb->getPosition() - u_normal * (b->radius - depth);
    return { A, B, u_normal, depth };
}

auto CircleCollider::testCollision(TransformComponent* tr, BodyCollider* other, TransformComponent* other_tr) -> Manifold {
    return other->testCollision(other_tr, this, tr);
}
auto CircleCollider::testCollision(TransformComponent* tr, CircleCollider* other, TransformComponent* other_tr) -> Manifold {
    return findManifold(this, tr, other, other_tr);
}