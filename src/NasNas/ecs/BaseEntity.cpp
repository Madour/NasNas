/**
* Created by Modar Nasser on 15/04/2020.
**/


#include <cmath>
#include "NasNas/core/data/Config.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;

ecs::old::BaseEntity::BaseEntity(const std::string& name) :
ecs::ComponentGroup(name)
{
    add<ecs::TransformComponent>();
}

auto ecs::old::BaseEntity::transform() const -> ecs::Transform* {
    return get<ecs::Transform>();
}

auto ecs::old::BaseEntity::inputs() const -> ecs::old::Inputs* {
    return get<ecs::old::Inputs>();
}

auto ecs::old::BaseEntity::physics() const -> ecs::Physics* {
    return get<ecs::Physics>();
}

auto ecs::old::BaseEntity::collider() const -> ecs::Collider* {
    return get<ecs::Collider>();
}
