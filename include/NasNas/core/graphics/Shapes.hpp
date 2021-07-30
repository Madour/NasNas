/**
* Created by Modar Nasser on 24/08/2020.
**/

#pragma once

#include <optional>
#include <SFML/Graphics.hpp>
#include "NasNas/core/data/Maths.hpp"
#include "NasNas/core/data/Rect.hpp"

namespace ns {
    class EllipseShape : public sf::Shape {
    public :

        EllipseShape() = default;
        explicit EllipseShape(const sf::Vector2f& radius);
        EllipseShape(float radius_x, float radius_y);

        void setRadius(const sf::Vector2f& radius)  ;

        auto getRadius() const -> const sf::Vector2f&;

        void setPointCount(std::size_t point_count);

        auto getPointCount() const -> std::size_t override;

        auto getPoint(std::size_t index) const -> sf::Vector2f override;

    private :
        std::size_t m_point_cout = 30;
        sf::Vector2f m_radius;
    };

    class LineShape : public sf::Drawable, public sf::Transformable {
    public:
        LineShape();
        void addPoint(float x, float y, const std::optional<sf::Color>& color=std::nullopt);
        void addPoint(const sf::Vector2f& position, const std::optional<sf::Color>& color=std::nullopt);
        void setPoint(unsigned int index, const sf::Vector2f& position);
        void setPoint(unsigned int index, float x, float y);

        void removePoint(unsigned int index);

        void setColor(const sf::Color& color);
        void setColor(unsigned int index, const sf::Color& color);

        auto getLocalBounds() const -> sf::FloatRect;
        auto getGlobalBounds() const -> ns::FloatRect;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::Color m_color;
        sf::VertexArray m_vertices;
    };
}
