/**
* Created by Modar Nasser on 15/04/2020.
**/

#pragma once

#include "NasNas/data/AppComponent.hpp"
#include "NasNas/core/Spritesheet.hpp"
#include "NasNas/ecs/GraphicsComponent.hpp"

namespace ns {

class BaseEntity: public Drawable {
    public:
        explicit BaseEntity(const std::string& name);
        ~BaseEntity() override;

        template<typename T, typename... TArgs>
        void addComponent(TArgs... component_args);

        template<typename T>
        void addComponent(T* new_component);

        virtual void update();

        auto getPosition() -> sf::Vector2f override;
        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);

        auto getX() const -> float;
        void setX(float value);

        auto getY() const -> float;
        void setY(float value);

        auto getVelocity() const -> sf::Vector2f;
        void setVelocity(float dx, float dy);

        void move(float offsetx, float offsety) override;

    private:
        std::string m_name;

        int m_gx = 0, m_gy = 0;
        float m_rx = 0, m_ry = 0;

        sf::Vector2f m_acceleration = {1, 1};

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    protected:
        sf::Vector2f m_velocity = {0, 0};
        std::vector<ecs::BaseComponent*> m_components_list;
        std::vector<ecs::BaseComponent*> m_owned_components_list;
        std::vector<ecs::GraphicsComponent*> m_graphics_components_list;
    };

    template<typename T, typename... TArgs>
    void BaseEntity::addComponent(TArgs... component_args) {
        static_assert(std::is_base_of_v<ecs::BaseComponent, T>, "`component` argument of addComponent must be derived from BaseComponent.");
        auto* new_component = new T(std::forward<TArgs>(component_args)...);
        m_components_list.push_back(new_component);
        m_owned_components_list.push_back(new_component);
        if (std::is_base_of_v<ecs::GraphicsComponent, T>) {
            m_graphics_components_list.push_back(new_component);
        }
    }

    template<typename T>
    void BaseEntity::addComponent(T* new_component) {
        static_assert(std::is_base_of_v<ecs::BaseComponent, T>, "`component` argument of addComponent must be derived from BaseComponent.");
        m_components_list.push_back(new_component);
        if (std::is_base_of_v<ecs::GraphicsComponent, T>) {
            m_graphics_components_list.push_back(new_component);
        }
    }


}
