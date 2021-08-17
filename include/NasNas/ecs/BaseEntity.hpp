/**
* Created by Modar Nasser on 15/04/2020.
**/


#pragma once

#include <memory>
#include "NasNas/ecs/ComponentGroup.hpp"

namespace ns {

    class BaseEntity : public ecs::ComponentGroup {
    public:
        explicit BaseEntity(const std::string& name);

        auto transform() const -> ecs::Transform*;
        auto inputs() const -> ecs::old::Inputs*;
        auto physics() const -> ecs::Physics*;
        auto collider() const -> ecs::Collider*;

    };

    template<class T, typename... TArgs>
    void BaseEntity::addComponent(TArgs... component_args) {
        addComponent(std::make_shared<T>(this, std::forward<TArgs>(component_args)...));
    }

    template<typename T>
    void BaseEntity::addComponent(std::shared_ptr<T> new_component) {
        static_assert(std::is_base_of_v<ecs::BaseComponent, T>, "New component type must be derived from BaseComponent.");

        if constexpr (std::is_base_of_v<ecs::GraphicsComponent, T>)
            m_graphics_components_list.push_back(new_component.get());
        else if constexpr (std::is_same_v<ecs::PhysicsComponent, T>)
            m_physics_component = new_component.get();
        else if constexpr (std::is_same_v<ecs::InputsComponent, T>)
            m_inputs_component = new_component.get();
        else if constexpr (std::is_same_v<ecs::ColliderComponent, T>)
            m_collider_component = new_component.get();

        m_components_list.push_back(new_component);
    }

    template<typename T>
    void BaseEntity::addComponent(T* new_component) {
        addComponent(std::shared_ptr<T>(new_component));
    }

    template <typename T>
    auto BaseEntity::graphics(unsigned int index) -> T* {
        if (index < m_graphics_components_list.size()) {
            auto ptr = dynamic_cast<T*>(m_graphics_components_list[index]);
            if (ptr != nullptr)
                return ptr;
            std::cout << "Entity «" << m_name << "»'s graphic component number " << index << " is not of type "
                      << typeid(T).name() << std::endl;
            exit(-1);
        }
        std::cout << "Entity «" << m_name << "» has less than " << index << " graphics components. Index out of range." << std::endl;
        exit(-1);
    }

}
