/**
* Created by Modar Nasser on 24/08/2020.
**/

#include <NasNas/core/graphics/Shapes.hpp>

#include <NasNas/core/data/Maths.hpp>

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
    m_point_count = point_count;
    update();
}

auto EllipseShape::getPointCount() const -> std::size_t {
    return m_point_count;
}

auto EllipseShape::getPoint(std::size_t index) const -> sf::Vector2f {
    float angle = index * 2 * ns::PI / m_point_count - ns::PI / 2;
    float x = std::cos(angle) * m_radius.x;
    float y = std::sin(angle) * m_radius.y;

    return sf::Vector2f(m_radius.x + x, m_radius.y + y);
}


LineShape::LineShape() : m_color(sf::Color::White) {
    m_shape_verts.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_outline_verts.setPrimitiveType(sf::PrimitiveType::Triangles);
}

void LineShape::resize(size_t size) {
    Point val{getPosition(), m_color, m_thickness/2.f};
    m_points.resize(size, val);
    update();
}

void LineShape::addPoint(float x, float y, const std::optional<sf::Color>& color) {
    addPoint({x, y}, color);
}

void LineShape::addPoint(const sf::Vector2f& point, const std::optional<sf::Color>& color) {
    if (!m_points.empty() && ns::distance(point, m_points.back().pos) <= m_points.back().radius)
        return;

    if (color.has_value())
        m_points.push_back({point, color.value(), m_thickness/2.f});
    else
        m_points.push_back({point, m_color, m_thickness/2.f});

    update();
    update(m_points.size()-1);
}

void LineShape::removePoint(unsigned index) {
    if (index < m_points.size()) {
        m_points.erase(std::remove(m_points.begin(), m_points.end(), m_points[index]), m_points.end());
        update();
        for (unsigned i = index; i < m_points.size(); ++i)
            update(i);
    }
}

void LineShape::setPoint(unsigned index, float x, float y) {
    setPoint(index, {x, y});
}

void LineShape::setPoint(unsigned index, const sf::Vector2f& position) {
    if (index < m_points.size()) {
        m_points[index].pos = position;
        update(index);
        update(index+1);
    }
}

auto LineShape::getPoint(unsigned index) const -> const sf::Vector2f& {
    return m_points[index].pos;
}

void LineShape::setColor(const sf::Color& color) {
    m_color = color;
}

auto LineShape::getColor() const -> const sf::Color& {
    return m_color;
}

void LineShape::setColor(unsigned index, const sf::Color& color) {
    if (index < m_points.size()) {
        m_points[index].color = color;
        update(index);
    }
}

auto LineShape::getColor(unsigned index) const -> const sf::Color& {
    return m_points[index].color;
}

void LineShape::setThickness(float thickness) {
    m_thickness = thickness;
}

auto LineShape::getThickness() const -> float {
    return m_thickness;
}

void LineShape::setThickness(unsigned int index, float thickness) {
    if (index < m_points.size()) {
        m_points[index].radius = thickness / 2.f;
        update(index);
    }
}

auto LineShape::getThickness(unsigned int index) const -> float {
    return m_points[index].radius * 2;
}

void LineShape::setOutlineThickness(float thickness) {
    m_outline_thickness = thickness;
}

auto LineShape::getOutlineThickness() const -> float {
    return m_outline_thickness;
}

void LineShape::setOutlineColor(const sf::Color& color) {
    m_outline_color = color;
}

auto LineShape::getOutlineColor() const -> const sf::Color& {
    return m_outline_color;
}

auto LineShape::getPointCount() const -> std::size_t {
    return m_points.size();
}

auto LineShape::getLocalBounds() const -> sf::FloatRect {
    return m_shape_verts.getBounds();
}

auto LineShape::getGlobalBounds() const -> ns::FloatRect {
    return getTransform().transformRect(m_shape_verts.getBounds());
}

void LineShape::update() {
    m_shape_verts.resize(m_points.size() * 6 * 2 - 6);
    m_outline_verts.resize(m_points.size() * 6 * 2 - 6);
}

void LineShape::update(unsigned int index) {
    if (m_points.size() > 1 && index > 0 && index < m_points.size()) {
        auto& A = m_points[index-1];
        auto& B = m_points[index];

        auto direction = (B.pos - A.pos) / ns::norm(B.pos - A.pos);
        auto normal = ns::normal(direction);

        auto A_up = A.pos - normal*A.radius;
        auto AR = A.pos + normal*A.radius;
        auto B_up = B.pos - normal*B.radius;
        auto B_down = B.pos + normal*B.radius;

        auto A_up_outline = A.pos - normal*(A.radius + m_outline_thickness);
        auto A_down_outline = A.pos + normal*(A.radius + m_outline_thickness);
        auto B_up_outline = B.pos - normal*(B.radius + m_outline_thickness);
        auto B_down_outline = B.pos + normal*(B.radius + m_outline_thickness);

        auto prev_joint_index = 2 * index - 2;
        auto section_index = 2 * index - 1;
        auto next_joint_index = 2 * index;

        if (prev_joint_index > 0) {
            m_shape_verts[prev_joint_index*6 + 0].position = AR;
            m_shape_verts[prev_joint_index*6 + 5].position = A_up;

            m_outline_verts[prev_joint_index*6 + 0].position = A_down_outline;
            m_outline_verts[prev_joint_index*6 + 5].position = A_up_outline;
        }

        m_shape_verts[section_index*6 + 0].position = A_up;
        m_shape_verts[section_index*6 + 1].position = AR;
        m_shape_verts[section_index*6 + 2].position = B_down;
        m_shape_verts[section_index*6 + 3].position = A_up;
        m_shape_verts[section_index*6 + 4].position = B_down;
        m_shape_verts[section_index*6 + 5].position = B_up;

        m_shape_verts[section_index*6 + 0].color = A.color;
        m_shape_verts[section_index*6 + 1].color = A.color;
        m_shape_verts[section_index*6 + 2].color = B.color;
        m_shape_verts[section_index*6 + 3].color = A.color;
        m_shape_verts[section_index*6 + 4].color = B.color;
        m_shape_verts[section_index*6 + 5].color = B.color;

        m_outline_verts[section_index*6 + 0].position = A_up_outline;
        m_outline_verts[section_index*6 + 1].position = A_down_outline;
        m_outline_verts[section_index*6 + 2].position = B_down_outline;
        m_outline_verts[section_index*6 + 3].position = A_up_outline;
        m_outline_verts[section_index*6 + 4].position = B_down_outline;
        m_outline_verts[section_index*6 + 5].position = B_up_outline;

        m_outline_verts[section_index*6 + 0].color = m_outline_color;
        m_outline_verts[section_index*6 + 1].color = m_outline_color;
        m_outline_verts[section_index*6 + 2].color = m_outline_color;
        m_outline_verts[section_index*6 + 3].color = m_outline_color;
        m_outline_verts[section_index*6 + 4].color = m_outline_color;
        m_outline_verts[section_index*6 + 5].color = m_outline_color;

        if (next_joint_index > 0) {
            m_shape_verts[next_joint_index*6 + 0].position = B_up;
            m_shape_verts[next_joint_index*6 + 1].position = B_up;
            m_shape_verts[next_joint_index*6 + 2].position = B_down;
            m_shape_verts[next_joint_index*6 + 3].position = B_up;
            m_shape_verts[next_joint_index*6 + 4].position = B_down;
            m_shape_verts[next_joint_index*6 + 5].position = B_up;

            m_shape_verts[next_joint_index*6 + 0].color = B.color;
            m_shape_verts[next_joint_index*6 + 1].color = B.color;
            m_shape_verts[next_joint_index*6 + 2].color = B.color;
            m_shape_verts[next_joint_index*6 + 3].color = B.color;
            m_shape_verts[next_joint_index*6 + 4].color = B.color;
            m_shape_verts[next_joint_index*6 + 5].color = B.color;

            m_outline_verts[next_joint_index*6 + 0].position = B_up_outline;
            m_outline_verts[next_joint_index*6 + 1].position = B_up_outline;
            m_outline_verts[next_joint_index*6 + 2].position = B_down_outline;
            m_outline_verts[next_joint_index*6 + 3].position = B_up_outline;
            m_outline_verts[next_joint_index*6 + 4].position = B_down_outline;
            m_outline_verts[next_joint_index*6 + 5].position = B_up_outline;

            m_outline_verts[next_joint_index*6 + 0].color = m_outline_color;
            m_outline_verts[next_joint_index*6 + 1].color = m_outline_color;
            m_outline_verts[next_joint_index*6 + 2].color = m_outline_color;
            m_outline_verts[next_joint_index*6 + 3].color = m_outline_color;
            m_outline_verts[next_joint_index*6 + 4].color = m_outline_color;
            m_outline_verts[next_joint_index*6 + 5].color = m_outline_color;
        }
    }
}

void LineShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_outline_verts, states);
    target.draw(m_shape_verts, states);
}

auto ns::LineShape::Point::operator==(const ns::LineShape::Point& p) const -> bool {
    return pos == p.pos && color == p.color && radius == p.radius;
}
