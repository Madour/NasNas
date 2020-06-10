/**
* Created by Modar Nasser on 10/06/2020.
**/

#include "NasNas/ecs/GraphicsComponent.hpp"

using namespace ns::ecs;

GraphicsComponent::GraphicsComponent(BaseEntity* entity) : BaseComponent(entity){
    m_entity = entity;
}

