/**
* Created by Modar Nasser on 09/06/2020.
**/


#include "NasNas/ecs/BaseComponent.hpp"

using namespace ns;
using namespace ns::ecs;

BaseComponent::BaseComponent(BaseEntity* entity) :
m_entity(entity)
{}

unsigned long BaseComponent::id_counter = 0;

auto BaseComponent::getNextId() -> unsigned long {
    return BaseComponent::id_counter++;
}
