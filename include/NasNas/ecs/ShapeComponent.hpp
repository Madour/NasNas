/**
* Created by Modar Nasser on 11/06/2020.
**/


#pragma once

#include "NasNas/data/Rect.hpp"
#include "NasNas/ecs/GraphicsComponent.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

namespace ns::ecs {

    template <typename T>
    class Shape : public GraphicsComponent{
    public:
        static auto getId() -> unsigned long;

        Shape(BaseEntity* entity, const T& shape, const sf::Vector2f& pos_offset={0, 0});

        auto getDrawable() -> T& override;
        auto getGlobalBounds() -> ns::FloatRect override;

        void update() override;

    private:
        static const unsigned long uid;

        T m_drawable;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    template<typename T>
    Shape<T>::Shape(BaseEntity* entity, const T& shape, const sf::Vector2f& pos_offset) :
    GraphicsComponent(entity),
    m_drawable(shape) {
        m_transform.translate(pos_offset);
    }

    template<typename T>
    auto Shape<T>::getDrawable() -> T& {
        return m_drawable;
    }

    template<typename T>
    auto Shape<T>::getGlobalBounds() -> ns::FloatRect {
        return ns::FloatRect(m_entity->transform()->getTransform().transformRect(
                m_transform.transformRect(m_drawable.getGlobalBounds())
        ));
    }

    template<typename T>
    void Shape<T>::update() {}

    template<typename T>
    void Shape<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= m_transform;
        target.draw(m_drawable, states);
    }

    typedef Shape<sf::CircleShape> CircleShape;
    typedef Shape<ns::EllipseShape> EllipseShape;
    typedef Shape<ns::LineShape> LineShape;
    typedef Shape<sf::RectangleShape> RectangleShape;
    typedef Shape<sf::ConvexShape> ConvexShape;

    template <typename T>
    auto Shape<T>::getId() -> unsigned long {
        return Shape<T>::uid;
    }
}
