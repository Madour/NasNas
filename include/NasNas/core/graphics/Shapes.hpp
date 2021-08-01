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
        struct Point {
            sf::Vector2f pos;
            sf::Color color;
            float radius=1.f;
            auto operator==(const Point& p1) const -> bool;
        };
    public:
        LineShape();

        void resize(size_t size);

        void addPoint(float x, float y, const std::optional<sf::Color>& color=std::nullopt);
        void addPoint(const sf::Vector2f& position, const std::optional<sf::Color>& color=std::nullopt);
        void removePoint(unsigned index);

        void setPoint(unsigned index, float x, float y);
        void setPoint(unsigned index, const sf::Vector2f& position);
        auto getPoint(unsigned index) const -> const sf::Vector2f&;

        void setColor(const sf::Color& color);
        auto getColor() const -> const sf::Color&;

        void setColor(unsigned index, const sf::Color& color);
        auto getColor(unsigned index) const -> const sf::Color&;

        void setThickness(float thickness);
        auto getThickness() const -> float;

        void setThickness(unsigned index, float thickness);
        auto getThickness(unsigned index) const -> float;

        void setOutlineThickness(float thickness);
        auto getOutlineThickness() const -> float;

        void setOutlineColor(const sf::Color& color);
        auto getOutlineColor() const -> const sf::Color&;

        auto getPointCount() const -> std::size_t;

        auto getLocalBounds() const -> sf::FloatRect;
        auto getGlobalBounds() const -> ns::FloatRect;

    private:
        void update();
        void update(unsigned index);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::Color m_color=sf::Color::White;
        sf::Color m_outline_color=sf::Color::Black;
        float m_thickness = 1.f;
        float m_outline_thickness = 0.f;
        std::vector<Point> m_points;
        sf::VertexArray m_shape_verts;
        sf::VertexArray m_outline_verts;
    };

}
