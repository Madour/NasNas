/**
* Created by Modar Nasser on 09/06/2020.
**/

#include "NasNas/ecs/BaseComponent.hpp"

using namespace ns::ecs;
using namespace ns;

BaseComponent::BaseComponent(BaseEntity* entity) {
    m_entity = entity;
}

BaseComponent::~BaseComponent() = default;
