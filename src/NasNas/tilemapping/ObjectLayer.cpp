/**
* Created by Modar Nasser on 22/08/2020.
**/

#include "NasNas/tilemapping/ObjectLayer.hpp"

using namespace ns;
using namespace ns::tm;

template <>
ns::tm::ObjectLayer::Object<sf::RectangleShape>::Object(const pugi::xml_node& xml_node, const sf::Color& color) :
ObjectLayer::Object<sf::RectangleShape>(
    xml_node.attribute("id").as_uint(),
    xml_node.attribute("x").as_float(),
    xml_node.attribute("y").as_float()
) {
    parseProperties(xml_node.child("properties"));
    if (xml_node.attribute("width")) { // rectangle
        m_shape.setSize({xml_node.attribute("width").as_float(), xml_node.attribute("height").as_float()});
        m_shape.setRotation(xml_node.attribute("rotation").as_float());
        m_shape.setFillColor(sf::Color(color.r, color.g, color.b, 40));
        m_shape.setOutlineThickness(1);
        m_shape.setOutlineColor(color);
    }
    else { // point
        m_shape.setSize({1, 1});
        m_shape.setFillColor(color);
    }
}

template <>
ns::tm::ObjectLayer::Object<sf::EllipseShape>::Object(const pugi::xml_node& xml_node, const sf::Color& color) :
ObjectLayer::Object<sf::EllipseShape>(
    xml_node.attribute("id").as_uint(),
    xml_node.attribute("x").as_float(),
    xml_node.attribute("y").as_float()
) {
    m_shape.setRadius({xml_node.attribute("width").as_float()/2.f, xml_node.attribute("height").as_float()/2.f});
    m_shape.setRotation(xml_node.attribute("rotation").as_float());
    m_shape.setFillColor(sf::Color(color.r, color.g, color.b, 40));
    m_shape.setOutlineThickness(1);
    m_shape.setOutlineColor(color);
}

template <>
ns::tm::ObjectLayer::Object<sf::ConvexShape>::Object(const pugi::xml_node& xml_node, const sf::Color& color) :
ObjectLayer::Object<sf::ConvexShape>(
    xml_node.attribute("id").as_uint(),
    xml_node.attribute("x").as_float(),
    xml_node.attribute("y").as_float()
) {
    parseProperties(xml_node.child("properties"));
    auto points = ObjectLayer::stringToPoints(xml_node.child("polygon").attribute("points").as_string());
    m_shape.setPointCount(points.size());
    for (unsigned int i = 0; i < points.size(); i++)
        m_shape.setPoint(i, points[i]);
    m_shape.setRotation(xml_node.attribute("rotation").as_float());
    m_shape.setFillColor(sf::Color(color.r, color.g, color.b, 40));
    m_shape.setOutlineThickness(1);
    m_shape.setOutlineColor(color);
}

template <>
ns::tm::ObjectLayer::Object<sf::LineShape>::Object(const pugi::xml_node& xml_node, const sf::Color& color) :
ObjectLayer::Object<sf::LineShape>(
    xml_node.attribute("id").as_uint(),
    xml_node.attribute("x").as_float(),
    xml_node.attribute("y").as_float()
) {
    parseProperties(xml_node.child("properties"));
    auto points = ObjectLayer::stringToPoints(xml_node.child("polyline").attribute("points").as_string());
    for (const auto& point : points)
        m_shape.addPoint(point);
    m_shape.setRotation(xml_node.attribute("rotation").as_float());
    m_shape.setColor(color);
}


ns::tm::ObjectLayer::ObjectLayer(const pugi::xml_node& xml_node, tm::TiledMap* tiledmap) :
Layer(xml_node, tiledmap) {
    if (xml_node.attribute("color"))
        m_color = toColor(std::string(xml_node.attribute("color").as_string()));
    for (const auto& object : xml_node.children("object")) {
        if(object.child("ellipse")) {
            Object<sf::EllipseShape> r{object, m_color};
            m_ellipses.push_back(r);
        }
        else if(object.child("polyline")) {
            Object<sf::LineShape> r{object, m_color};
            m_polylines.push_back(r);
        }
        else if(object.child("polygon")) {
            Object<sf::ConvexShape> r{object, m_color};
            m_polygons.push_back(r);
        }
        else if(object.attribute("gid")) {
            // not yet implemented
        }
        else if (object.attribute("point")) {
            Object<sf::RectangleShape> r{object, m_color};
            m_points.push_back(r);
        }
        else {
            Object<sf::RectangleShape> r{object, m_color};
            m_rectangles.push_back(r);
        }
    }
}

auto ObjectLayer::getRectangles() -> std::vector<Object<sf::RectangleShape>>& {
    return m_rectangles;
}

auto ObjectLayer::getPoints() -> std::vector<Object<sf::RectangleShape>>& {
    return m_points;
}

auto ObjectLayer::getEllipses() -> std::vector<Object<sf::EllipseShape>>& {
return m_ellipses;
}

auto ObjectLayer::getPolygons() -> std::vector<Object<sf::ConvexShape>>& {
    return m_polygons;
}

auto ObjectLayer::getPolylines() -> std::vector<Object<sf::LineShape>>& {
    return m_polylines;
}

auto ObjectLayer::getRectangle(unsigned int id) -> const Object<sf::RectangleShape>& {
    for (auto& object : m_rectangles) {
        if (object.getId() == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Rectangle object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getPoint(unsigned int id) -> const Object<sf::RectangleShape>& {
    for (auto& object : m_points) {
        if (object.getId() == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Point object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getEllipse(unsigned int id) -> const Object<sf::EllipseShape>& {
    for (auto& object : m_ellipses) {
        if (object.getId() == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Ellipse object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getPolygon(unsigned int id) -> const Object<sf::ConvexShape>& {
    for (auto& object : m_polygons) {
        if (object.getId() == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Polygon object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getPolyline(unsigned int id) -> const ObjectLayer::Object<sf::LineShape>& {
    for (auto& object : m_polylines) {
        if (object.getId() == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Polyline object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getGlobalBounds() -> ns::FloatRect {
    return ns::FloatRect(
        m_transformable.getPosition(),
        {(float)(m_tiledmap->getSize().x*m_tiledmap->getTileSize().x), (float)(m_tiledmap->getSize().y*m_tiledmap->getTileSize().y)}
    );
}

void ObjectLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& rect : m_rectangles)
        target.draw(rect.getShape());

    for (const auto& point : m_points)
        target.draw(point.getShape());

    for (const auto& ellipse : m_ellipses)
        target.draw(ellipse.getShape());

    for (const auto& polygon : m_polygons)
        target.draw(polygon.getShape());

    for (const auto& polygon : m_polylines)
        target.draw(polygon.getShape());
}

auto ObjectLayer::stringToPoints(const char* points_str) -> std::vector<sf::Vector2f> {
    std::vector<sf::Vector2f> result;
    sf::Vector2f temp = {0, 0}; sf::Vector2f sign = {1, 1}; bool storing_x = true;
    while (*points_str != '\0') {
        switch (*points_str) {
            case ',':
                storing_x = false;
                break;
            case ' ':
                result.emplace_back(temp.x*sign.x, temp.y*sign.y);
                temp = {0, 0}; sign = {1, 1}; storing_x = true;
                break;
            case '-':
                if (storing_x) sign.x *= -1;
                else sign.y *= -1;
                break;
            default:
                if (storing_x) {
                    temp.x *= 10;
                    temp.x += (float)(*points_str - '0');
                } else {
                    temp.y *= 10;
                    temp.y += (float)(*points_str - '0');
                }
                break;
        }
        points_str++;
    }
    result.emplace_back(temp.x*sign.x, temp.y*sign.y);
    return result;
}
