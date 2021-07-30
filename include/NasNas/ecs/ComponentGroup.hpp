// Created by Modar Nasser on 06/02/2021.

#pragma once

#include "NasNas/ecs/BaseComponent.hpp"
#include "NasNas/ecs/GraphicsComponent.hpp"
#include "NasNas/ecs/TransformComponent.hpp"
#include "NasNas/ecs/PhysicsComponent.hpp"
#include "NasNas/ecs/InputsComponent.hpp"
#include "NasNas/ecs/ColliderComponent.hpp"

namespace ns::ecs {

    class ComponentGroup : public sf::Drawable {
    public:
        explicit ComponentGroup(std::string name);
        ~ComponentGroup() override;

        template <typename T, typename... TArgs>
        void add(TArgs... component_args);

        template <typename T>
        void add(T* new_component);

        template <typename T>
        auto get() const -> T*;

        template <typename T>
        void remove();

        void addChild(const std::string& name);
        auto getChild(const std::string& name) const -> ComponentGroup*;
        void removeChild(const std::string& name);

        auto getParent() const -> ComponentGroup*;

        virtual void update();

        auto getPosition() const -> sf::Vector2f;
        auto getGlobalBounds() const -> ns::FloatRect;

    protected:
        auto graphics() -> const std::vector<GraphicsComponent*>&;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::string m_name;

        std::unordered_map<int, BaseComponent*> m_components;
        std::vector<GraphicsComponent*> m_graphics;

        std::map<std::string, ComponentGroup*> m_childs;
        ComponentGroup* m_parent = nullptr;

    };

    template<class T, typename... TArgs>
    void ComponentGroup::add(TArgs... component_args) {
        add(new T(std::forward<TArgs>(component_args)...));
    }

    template<typename T>
    void ComponentGroup::add(T* new_component) {
        new_component->m_owner = this;
        remove<T>();
        m_components[T::uid] = new_component;
        if constexpr (std::is_base_of_v<GraphicsComponent, T>)
            m_graphics.push_back(new_component);
    }

    template <typename T>
    auto ComponentGroup::get() const -> T* {
        if (m_components.count(T::uid))
            return static_cast<T*>(m_components.at(T::uid));
        return nullptr;
    }

    template <typename T>
    void ComponentGroup::remove() {
        const auto& it = m_components.find(T::uid);
        if (it != m_components.end()) {
            if constexpr (std::is_base_of_v<GraphicsComponent, T>) {
                m_graphics.erase(std::find(m_graphics.begin(), m_graphics.end(), static_cast<T*>(it->second)));
            }
            delete it->second;
            m_components.erase(it);
        }
    }

}
