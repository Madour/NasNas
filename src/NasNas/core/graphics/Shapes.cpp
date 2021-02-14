/**
* Created by Modar Nasser on 24/08/2020.
**/

#include "NasNas/core/graphics/Shapes.hpp"

using namespace ns;

EllipseShape::EllipseShape(float radius_x, float radius_y) :
EllipseShape(sf::Vector2f(radius_x, radius_y))
{}

EllipseShape::EllipseShape(const sf::Vector2f& radius) :
m_radius(radius) {
    update();
}

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


LineShape::LineShape() : m_color(sf::Color::White) {
    m_vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);
}

void LineShape::addPoint(float x, float y, const std::optional<sf::Color>& color) {
    m_vertices.append({sf::Vector2f(x, y), (color.has_value() ? color.value() : m_color)});
}

void LineShape::addPoint(const sf::Vector2f& point, const std::optional<sf::Color>& color) {
    m_vertices.append({point, (color.has_value() ? color.value() : m_color)});
}

void LineShape::setPoint(unsigned int index, const sf::Vector2f& position) {
    if (index < m_vertices.getVertexCount())
        m_vertices[index].position = position;
}

void LineShape::setPoint(unsigned int index, float x, float y) {
    if (index < m_vertices.getVertexCount())
        m_vertices[index].position = {x, y};
}

void LineShape::removePoint(unsigned int index) {
    if (index < m_vertices.getVertexCount()) {
        for (unsigned int i = index; i < m_vertices.getVertexCount()-1; ++i)
            m_vertices[i] = m_vertices[i+1];
        m_vertices.resize(m_vertices.getVertexCount()-1);
    }
    else {
        std::cerr << "Can't remove point " << index << ". "
                  << "LineShape has only " << m_vertices.getVertexCount() << " points."
                  << std::endl;
    }
}

void LineShape::setColor(const sf::Color& color) {
    m_color = color;
    for (unsigned int i = 0; i < m_vertices.getVertexCount(); ++i)
        m_vertices[i].color = color;
}

void LineShape::setColor(unsigned int index, const sf::Color& color) {
    if (index < m_vertices.getVertexCount())
        m_vertices[index].color = color;
    else {
        std::cerr << "Can't set color of point " << index << ". "
                  << "LineShape has only " << m_vertices.getVertexCount() << " points."
                  << std::endl;
    }
}

auto LineShape::getLocalBounds() const -> sf::FloatRect {
    return m_vertices.getBounds();
}

auto LineShape::getGlobalBounds() const -> ns::FloatRect {
    return getTransform().transformRect(m_vertices.getBounds());
}

void LineShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_vertices, states);
}
