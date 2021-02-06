/**
* Created by Modar Nasser on 11/06/2020.
**/


#pragma once

#include "NasNas/data/Rect.hpp"
#include "NasNas/ecs/GraphicsComponent.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

namespace ns::ecs {

    template <typename T>
    class ShapeComponent :  public Component<ShapeComponent<T>> , public GraphicsComponent {
    public:
        explicit ShapeComponent(const T& shape, const sf::Vector2f& pos_offset={0, 0});

        auto getDrawable() -> T& override;
        auto getGlobalBounds() -> ns::FloatRect override;

        void update() override;

    private:
        T m_drawable;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    template<typename T>
    ShapeComponent<T>::ShapeComponent(const T& shape, const sf::Vector2f& pos_offset) :
    m_drawable(shape) {
        m_transform.translate(pos_offset);
    }

    template<typename T>
    auto ShapeComponent<T>::getDrawable() -> T& {
        return m_drawable;
    }

    template<typename T>
    auto ShapeComponent<T>::getGlobalBounds() -> ns::FloatRect {
        if (this->m_owner->template get<Transform>()) {
            return this->m_owner->template get<Transform>()->getTransform().transformRect(
                    m_transform.transformRect(m_drawable.getGlobalBounds())
            );
        }
        return m_transform.transformRect(m_drawable.getGlobalBounds());
    }

    template<typename T>
    void ShapeComponent<T>::update() {}

    template<typename T>
    void ShapeComponent<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= m_transform;
        target.draw(m_drawable, states);
    }

    typedef ShapeComponent<sf::CircleShape> CircleShape;
    typedef ShapeComponent<ns::EllipseShape> EllipseShape;
    typedef ShapeComponent<ns::LineShape> LineShape;
    typedef ShapeComponent<sf::RectangleShape> RectangleShape;
    typedef ShapeComponent<sf::ConvexShape> ConvexShape;

}
