/**
* Created by Modar Nasser on 09/06/2020.
**/


#pragma once

#include "NasNas/data/Shapes.hpp"

namespace ns::ecs {
    class ComponentGroup;

    class BaseComponent {
        friend ComponentGroup;
    public:
        virtual ~BaseComponent() = default;
        virtual void update() = 0;
    protected:
        static auto getNextId() -> unsigned long;
        ComponentGroup* m_owner = nullptr;
    private:
        static unsigned long id_counter;
    };

    template <typename T>
    class Component : public BaseComponent {
    public:
        static auto getId() -> unsigned long;
    protected:
    private:
        static unsigned long uid;
    };

    template <typename T>
    unsigned long Component<T>::uid = BaseComponent::getNextId();

    template <typename T>
    auto Component<T>::getId() -> unsigned long {
        return uid;
    }

}
