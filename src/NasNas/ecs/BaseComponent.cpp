/**
* Created by Modar Nasser on 09/06/2020.
**/


#include "NasNas/ecs/BaseComponent.hpp"

using namespace ns;
using namespace ns::ecs;

BaseComponent::BaseComponent(BaseEntity* entity) {
    m_entity = entity;
}
