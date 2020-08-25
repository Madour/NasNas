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


LineShape::LineShape() = default;

void LineShape::addPoint(float x, float y) {
    m_vertices.emplace_back(sf::Vector2f(x, y));
}

void LineShape::addPoint(const Vector2f& point) {
    m_vertices.emplace_back(point);
}

void LineShape::removePoint(unsigned int index) {
    if (index < m_vertices.size()) {
        m_vertices.erase(m_vertices.begin() + index);
    }
    else {
        std::cout << "Can't remove point " << index << ". "
                  << "LineShape has only " << m_vertices.size() << " points."
                  << std::endl;
    }
}

void LineShape::setColor(const sf::Color& color) {
    for (auto& vert : m_vertices)
        vert.color = color;
}

void LineShape::setColor(unsigned int index, const Color& color) {
    if (index < m_vertices.size())
        m_vertices[index].color = color;
    else {
        std::cout << "Can't set color of point " << index << ". "
                  << "LineShape has only " << m_vertices.size() << " points."
                  << std::endl;
    }
}

auto LineShape::getPosition() -> Vector2f {
    return Transformable::getPosition();
}

auto LineShape::getGlobalBounds() -> ns::FloatRect {
    VertexArray va;
    va.resize(m_vertices.size());
    for (const auto& vert : m_vertices) {
        va.append(vert);
    }
    return ns::FloatRect(getTransform().transformRect(va.getBounds()));
}

void LineShape::draw(RenderTarget& target, RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_vertices.data(), m_vertices.size(), PrimitiveType::LineStrip, states);
}
