/**
* Created by Modar Nasser on 15/04/2020.
**/


#pragma once

#include <memory>
#include "NasNas/data/Drawable.hpp"
#include "NasNas/ecs/GraphicsComponent.hpp"
#include "NasNas/ecs/PhysicsComponent.hpp"
#include "NasNas/ecs/InputsComponent.hpp"
#include "NasNas/ecs/ColliderComponent.hpp"

namespace ns {

    class BaseEntity : public ns::Drawable {
    public:
        explicit BaseEntity(std::string name);
        ~BaseEntity() override;

        template <typename T, typename... TArgs>
        void add(TArgs... component_args);

        template <typename T>
        void add(T* new_component);

        template <typename T>
        auto get() const -> T*;

        virtual void update();

        auto getPosition() const -> sf::Vector2f override;

        void setX(float value);
        void setY(float value);

        auto getGlobalBounds() const -> ns::FloatRect override;

        auto transform() -> sf::Transformable*;
        auto inputs() const -> ecs::Inputs*;
        auto physics() const -> ecs::Physics*;
        auto collider() const -> ecs::Collider*;
        auto graphics() -> std::vector<ecs::GraphicsComponent*>&;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::string m_name;
        sf::Transformable m_transformable;

        std::vector<ecs::BaseComponent*> m_components;
        std::vector<ecs::GraphicsComponent*> m_graphics;

    };

    template<class T, typename... TArgs>
    void BaseEntity::add(TArgs... component_args) {
        add(new T(this, std::forward<TArgs>(component_args)...));
    }

    template<typename T>
    void BaseEntity::add(T* new_component) {
        m_components[T::getId()] = new_component;
        if constexpr (std::is_base_of_v<ecs::GraphicsComponent, T>)
            m_graphics.push_back(new_component);
    }

    template <typename T>
    auto BaseEntity::get() const -> T* {
        return static_cast<T*>(m_components[T::getId()]);
    }
}
