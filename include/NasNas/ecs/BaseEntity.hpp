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
        explicit BaseEntity(const std::string& name);
        ~BaseEntity() override;

        template<class T, typename... TArgs>
        void addComponent(TArgs... component_args);

        template<typename T>
        void addComponent(std::shared_ptr<T> new_component);

        template<typename T>
        void addComponent(T* new_component);

        virtual void update();

        auto getPosition() -> sf::Vector2f override;

        void setX(float value);
        void setY(float value);

        auto getGlobalBounds() -> ns::FloatRect override;
        void move(float offsetx, float offsety);

        auto transform() -> sf::Transformable*;
        auto inputs() -> ecs::InputsComponent*;
        auto physics() -> ecs::PhysicsComponent*;
        auto graphics() -> std::vector<ecs::GraphicsComponent*>&;
        template<typename T>
        auto graphics(unsigned int index) -> T*;
        auto collider() -> ecs::ColliderComponent*;

    private:
        std::string m_name;

        int m_gx = 0, m_gy = 0;
        float m_rx = 0, m_ry = 0;
        sf::Transformable m_transformable;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        friend ecs::InputsComponent;
        friend ecs::PhysicsComponent;
        friend ecs::GraphicsComponent;
        friend ecs::ColliderComponent;
        std::vector<std::shared_ptr<ecs::BaseComponent>> m_components_list;
        std::vector<ecs::GraphicsComponent*> m_graphics_components_list;
        ecs::PhysicsComponent* m_physics_component = nullptr;
        ecs::InputsComponent* m_inputs_component = nullptr;
        ecs::ColliderComponent* m_collider_component = nullptr;

    };

    template<class T, typename... TArgs>
    void BaseEntity::addComponent(TArgs... component_args) {
        static_assert(std::is_base_of_v<ecs::BaseComponent, T>, "New component type must be derived from BaseComponent.");
        auto new_component = std::make_shared<T>(this, std::forward<TArgs>(component_args)...);
        m_components_list.push_back(new_component);
    }

    template<typename T>
    void BaseEntity::addComponent(std::shared_ptr<T> new_component) {
        static_assert(std::is_base_of_v<ecs::BaseComponent, T>, "New component type must be derived from BaseComponent.");
        m_components_list.push_back(new_component);
    }

    template<typename T>
    void BaseEntity::addComponent(T* new_component) {
        static_assert(std::is_base_of_v<ecs::BaseComponent, T>, "New component type must be derived from BaseComponent.");
        m_components_list.emplace_back(new_component);
    }

    template <typename T>
    auto BaseEntity::graphics(unsigned int index) -> T* {
        if (index < m_graphics_components_list.size()) {
            return dynamic_cast<T*>(m_graphics_components_list[index]);
        }
        std::cout << "Entity «" << m_name << "» has less than " << index << " graphics components. Index out of range." << std::endl;
        exit(-1);
    }

}
