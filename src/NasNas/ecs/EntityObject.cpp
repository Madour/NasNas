// Created by Modar Nasser on 28/08/2021.

#include "NasNas/ecs/EntityObject.hpp"

using namespace ns;

EntityObject::EntityObject() {
    id = Ecs.create();
}

EntityObject::~EntityObject() {
    Ecs.destroy(id);
}

namespace ns {
    ecs::detail::Registry<ecs::Entity> Ecs;
}