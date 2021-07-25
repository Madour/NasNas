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
    return { A, B, -u_normal, depth };
}

auto ns::ecs::findManifold(RectangleCollider* a, TransformComponent* ta, RectangleCollider* b, TransformComponent* tb) -> Manifold {
    sf::Vector2f nearest;
    nearest.x = std::clamp(ta->getPosition().x, tb->getPosition().x, tb->getPosition().x+b->width);
    nearest.y = std::clamp(ta->getPosition().y, tb->getPosition().y, tb->getPosition().y+b->height);
    auto normal = nearest - ta->getPosition();
    auto u_normal = normal / ns::norm(normal);
    auto depth = a->width - ns::norm(normal);
    auto A = ta->getPosition() + u_normal * b->width;
    auto B = nearest;
    return { A, B, -u_normal, depth };
}

auto ns::ecs::findManifold(CircleCollider* a, TransformComponent* ta, RectangleCollider* b, TransformComponent* tb) -> Manifold {
    sf::Vector2f nearest;
    nearest.x = std::clamp(ta->getPosition().x, tb->getPosition().x, tb->getPosition().x+b->width);
    nearest.y = std::clamp(ta->getPosition().y, tb->getPosition().y, tb->getPosition().y+b->height);
    auto normal = nearest - ta->getPosition();
    auto u_normal = normal / ns::norm(normal);
    auto depth = a->radius - ns::norm(normal);
    if (ns::norm(normal) == 0) {
        u_normal = {0, 1};
        depth = 0;
    }
    auto A = ta->getPosition() + u_normal * a->radius;
    auto B = nearest;
    return { A, B, -u_normal, depth };
}


auto CircleCollider::testCollision(TransformComponent* tr, BodyCollider* other, TransformComponent* other_tr) -> Manifold {
    return other->testCollision(other_tr, this, tr);
}
auto CircleCollider::testCollision(TransformComponent* tr, CircleCollider* other, TransformComponent* other_tr) -> Manifold {
    return findManifold(this, tr, other, other_tr);
}
auto CircleCollider::testCollision(TransformComponent* tr,RectangleCollider* other, TransformComponent* other_tr) -> Manifold {
    return findManifold(this, tr, other, other_tr);
}

auto RectangleCollider::testCollision(TransformComponent* tr, BodyCollider* other, TransformComponent* other_tr) -> Manifold {
    return other->testCollision(other_tr, this, tr);
}
auto RectangleCollider::testCollision(TransformComponent* tr, CircleCollider* other, TransformComponent* other_tr) -> Manifold {
    auto m = other->testCollision(other_tr, this, tr);
    auto temp = m.A;
    m.A = m.B;
    m.B = m.A;
    m.normal *= -1.f;
    return m;
}
auto RectangleCollider::testCollision(TransformComponent* tr,RectangleCollider* other, TransformComponent* other_tr) -> Manifold {
    return findManifold(this, tr, other, other_tr);
}