/**
* Created by Modar Nasser on 09/06/2020.
**/


#pragma once

namespace ns {

    class BaseEntity;

}
namespace ns::ecs {

    class BaseComponent {
    public:
        explicit BaseComponent(BaseEntity* entity);
        virtual void update() = 0;

    protected:
        BaseEntity* m_entity;
    };

}
