/**
* Created by Modar Nasser on 11/06/2020.
**/


#pragma once

#include "NasNas/data/Rect.hpp"
#include "NasNas/ecs/GraphicsComponent.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

namespace ns::ecs {

    template <typename T>
    class ShapeComponent : public GraphicsComponent{
    public:
        ShapeComponent(BaseEntity* entity, float radius, int point_count=30, const sf::Vector2f& pos_offset={0,0});
        ShapeComponent(BaseEntity* entity, float radius, const sf::Vector2f& pos_offset={0,0});
        ShapeComponent(BaseEntity* entity, const sf::Vector2f& size, const sf::Vector2f& pos_offset={0,0});
        ShapeComponent(BaseEntity* entity, int point_count, const sf::Vector2f& pos_offset={0,0});

        auto getDrawable() -> T& override;
        auto getGlobalBounds() -> ns::FloatRect override;

        void update() override;

    private:
        sf::Vector2f m_pos_offset = {0, 0};
        T m_drawable;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    template<typename T>
    auto ShapeComponent<T>::getDrawable() -> T& {
        return m_drawable;
    }

    template<typename T>
    auto ShapeComponent<T>::getGlobalBounds() -> ns::FloatRect {
        return ns::FloatRect(m_drawable.getGlobalBounds());
    }

    template<typename T>
    void ShapeComponent<T>::update() {
        m_drawable.setPosition(m_entity->getPosition() + m_pos_offset);
    }

    template<typename T>
    void ShapeComponent<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_drawable, states);
    }

}
