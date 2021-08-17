/**
* Created by Modar Nasser on 15/04/2020.
**/


#include <cmath>
#include "NasNas/core/data/Config.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;

BaseEntity::BaseEntity(const std::string& name) :
ecs::ComponentGroup(name)
{
    add<ecs::TransformComponent>();
}

auto BaseEntity::transform() const -> ecs::Transform* {
    return get<ecs::Transform>();
}

auto BaseEntity::inputs() const -> ecs::old::Inputs* {
    return get<ecs::old::Inputs>();
}

auto BaseEntity::physics() const -> ecs::Physics* {
    return get<ecs::Physics>();
}

auto BaseEntity::collider() const -> ecs::Collider* {
    return get<ecs::Collider>();
}
