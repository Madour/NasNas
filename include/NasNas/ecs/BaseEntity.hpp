/**
* Created by Modar Nasser on 15/04/2020.
**/

#pragma once

#include "NasNas/data/AppComponent.hpp"
#include "NasNas/core/Spritesheet.hpp"
#include "NasNas/ecs/GraphicsComponent.hpp"
#include "NasNas/ecs/PhysicsComponent.hpp"

namespace ns {

class BaseEntity: public Drawable {
    public:
        explicit BaseEntity(const std::string& name);
        ~BaseEntity() override;

        template<class T, typename... TArgs>
        void addComponent(TArgs... component_args);

        template<typename T>
        void addComponent(std::shared_ptr<T> new_component);

        virtual void update();

        auto getPosition() -> sf::Vector2f override;
        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);

        auto getX() -> float;
        void setX(float value);

        auto getY() -> float;
        void setY(float value);

        auto graphics() -> std::vector<ecs::GraphicsComponent*>&;
        auto physics() -> ecs::PhysicsComponent*;

        void move(float offsetx, float offsety) override;

    private:
        std::string m_name;

        int m_gx = 0, m_gy = 0;
        float m_rx = 0, m_ry = 0;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    protected:
        friend ecs::PhysicsComponent; friend ecs::GraphicsComponent;
        std::vector<std::shared_ptr<ecs::BaseComponent>> m_components_list;
        std::vector<ecs::GraphicsComponent*> m_graphics_components_list;
        ecs::PhysicsComponent* m_physics_component = nullptr;

};

    template<class T, typename... TArgs>
    void BaseEntity::addComponent(TArgs... component_args) {
        static_assert(std::is_base_of_v<ecs::BaseComponent, T>, "New component type must be derived from BaseComponent.");
        auto new_component = std::make_shared<T>(std::forward<TArgs>(component_args)...);
        m_components_list.push_back(new_component);
    }

    template<typename T>
    void BaseEntity::addComponent(std::shared_ptr<T> new_component) {
        static_assert(std::is_base_of_v<ecs::BaseComponent, T>, "New component type must be derived from BaseComponent.");
        m_components_list.push_back(new_component);
    }


}
