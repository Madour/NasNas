// Created by Modar Nasser on 11/07/2021.

#include "NasNas/ecs/World.hpp"
#include "NasNas/ecs/ComponentGroup.hpp"

using namespace ns;
using namespace ns::ecs;

void World::add(ComponentGroup* obj){
    if (std::find(m_objects.begin(), m_objects.end(), obj) == m_objects.end())
        m_objects.emplace_back(obj);
}

void World::step() {
    for (auto* obj : m_objects) {
        if (obj->get<RigidBodyComponent>()){
            auto* body = obj->get<RigidBodyComponent>();

            // body->force.y += body->mass * 9.8f / float(ns::Config::Window::update_rate);
            if (body->mass > 0) {
                body->velocity += body->force / body->mass;
            }
            body->force = {0, 0};
            obj->get<TransformComponent>()->move(body->velocity);
            body->velocity *= 0.998f;
        }
    }

    for (auto* obj1 : m_objects) {
        for (auto* obj2 : m_objects) {
            if (obj1 == obj2) break;

            if (obj1->get<ColliderGroupComponent>() && obj2->get<ColliderGroupComponent>()) {
                auto& col1 = obj1->get<ColliderGroupComponent>()->collider();
                auto& col2 = obj2->get<ColliderGroupComponent>()->collider();

                auto& tr1 = *obj1->get<TransformComponent>();
                auto& tr2 = *obj2->get<TransformComponent>();
                auto& body1 = *obj1->get<RigidBodyComponent>();
                auto& body2 = *obj2->get<RigidBodyComponent>();

                auto normal = tr2.getPosition() - tr1.getPosition();

                if (ns::norm(normal) < col1.radius + col2.radius) {
                    auto manifold = findManifold(&col1, &tr1, &col2, &tr2);

                    auto rel_vel = body2.velocity - body1.velocity;
                    auto contact_vel = ns::dot_product(rel_vel, manifold.normal);
                    ns_LOG(manifold.A, manifold.B, manifold.normal, manifold.depth);

                    if (contact_vel > 0) continue;

                    auto restitution = std::min(body1.restitution, body2.restitution);
                    auto j = - contact_vel;
                    auto impulse = manifold.normal * j;

                    if (body1.mass > 0)
                        body1.velocity -= impulse;
                    if (body2.mass > 0)
                        body2.velocity += impulse;

                    rel_vel = body2.velocity - body1.velocity;
                    auto t = rel_vel - (manifold.normal * ns::dot_product(rel_vel, manifold.normal));
                    t = t / ns::norm(t);

                    auto jt = - ns::dot_product(manifold.normal, t);

                    impulse = t * j * std::sqrt(body1.friction * body2.friction);

                    // body1.velocity -= impulse;
                    // body2.velocity += impulse;

                    //body1.force += -body1.restitution*dir*depth/2.f;
                    //body2.force += body2.restitution*dir*depth/2.f;
                }
            }
        }
    }


}
