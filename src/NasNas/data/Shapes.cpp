/**
* Created by Modar Nasser on 24/08/2020.
**/

#include "NasNas/data/Shapes.hpp"

using namespace sf;

EllipseShape::EllipseShape(const sf::Vector2f& radius) :
m_radius(radius) {
    update();
}

EllipseShape::EllipseShape(float radius_x, float radius_y) :
EllipseShape(sf::Vector2f(radius_x, radius_y))
{}

void EllipseShape::setRadius(const sf::Vector2f& radius) {
    m_radius = radius;
    update();
}

auto EllipseShape::getRadius() const -> const sf::Vector2f& {
    return m_radius;
}

void EllipseShape::setPointCount(std::size_t point_count) {
    m_point_cout = point_count;
    update();
}

auto EllipseShape::getPointCount() const -> std::size_t {
    return m_point_cout;
}

auto EllipseShape::getPoint(std::size_t index) const -> sf::Vector2f {
    float angle = index * 2 * ns::PI / m_point_cout - ns::PI / 2;
    float x = std::cos(angle) * m_radius.x;
    float y = std::sin(angle) * m_radius.y;

    return sf::Vector2f(m_radius.x + x, m_radius.y + y);
}