/**
* Created by Modar Nasser on 09/06/2020.
**/


#pragma once

#include "NasNas/core/graphics/Shapes.hpp"

namespace ns::ecs {
    class ComponentGroup;

    class BaseComponent {
        friend ComponentGroup;
    public:
        virtual ~BaseComponent() = default;
        virtual void update() {}
    protected:
        static auto getNextId() -> unsigned long;
        ComponentGroup* m_owner = nullptr;
    private:
        static unsigned long id_counter;
    };

    template <typename T>
    class Component : public BaseComponent {
        friend ComponentGroup;
        static unsigned long uid;
    };

    template <typename T>
    unsigned long Component<T>::uid = BaseComponent::getNextId();

}
