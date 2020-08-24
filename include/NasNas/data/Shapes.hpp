/**
* Created by Modar Nasser on 24/08/2020.
**/

#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/data/Maths.hpp"

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
}
