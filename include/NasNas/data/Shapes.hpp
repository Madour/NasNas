/**
* Created by Modar Nasser on 24/08/2020.
**/

#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/data/Maths.hpp"
#include "NasNas/data/Drawable.hpp"

namespace sf {
    class EllipseShape : public Shape {
    public :

        explicit EllipseShape(const Vector2f& radius = Vector2f(0, 0));
        EllipseShape(float radius_x, float radius_y);

        void setRadius(const Vector2f& radius)  ;

        auto getRadius() const -> const Vector2f&;

        void setPointCount(std::size_t point_count);

        auto getPointCount() const -> std::size_t override;

        auto getPoint(std::size_t index) const -> Vector2f override;

    private :
        std::size_t m_point_cout = 30;
        Vector2f m_radius;
    };

    class LineShape : public ns::Drawable, public Transformable {
    public:
        LineShape();
        void addPoint(float x, float y);
        void addPoint(const Vector2f& point);
        void removePoint(unsigned int index);

        void setColor(const Color& color);
        void setColor(unsigned int index, const Color& color);

        auto getPosition() -> Vector2f override;
        auto getGlobalBounds() -> ns::FloatRect override;

    private:
        void draw(RenderTarget& target, RenderStates states) const override;
        std::vector<Vertex> m_vertices;
    };
}
