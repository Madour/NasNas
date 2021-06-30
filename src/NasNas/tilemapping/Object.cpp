// Created by Modar Nasser on 28/06/2021.

#include "NasNas/tilemapping/Object.hpp"

using namespace ns;
using namespace ns::tm;

auto stringToPoints(const char* points_str) -> std::vector<sf::Vector2f>;

Object::Object(const pugi::xml_node& xml_node) :
PropertiesContainer(xml_node.child("properties")),
id(xml_node.attribute("id").as_uint()),
name(xml_node.attribute("name").as_string()),
type(xml_node.attribute("type").as_string()),
x(xml_node.attribute("x").as_float()),
y(xml_node.attribute("y").as_float()),
rotation(xml_node.attribute("rotation").as_float())
{}

RectangleObject::RectangleObject(const pugi::xml_node& xml_node, const sf::Color& color) :
        ShapeObject<sf::RectangleShape>(xml_node, color),
        width(xml_node.attribute("width").as_float()),
        height(xml_node.attribute("height").as_float())
{
    m_shape.setSize({width, height});
}

EllipseObject::EllipseObject(const pugi::xml_node& xml_node, const sf::Color& color) :
        ShapeObject<ns::EllipseShape>(xml_node, color),
        width(xml_node.attribute("width").as_float()),
        height(xml_node.attribute("height").as_float())
{
    m_shape.setRadius({width/2.f, height/2.f});
}

PointObject::PointObject(const pugi::xml_node& xml_node, const sf::Color& color) :
        ShapeObject<sf::CircleShape>(xml_node, color)
{
    m_shape.setRadius(1.f);
    m_shape.setOrigin(1.f, 1.f);
}

PolylineObject::PolylineObject(const pugi::xml_node& xml_node, const sf::Color& color) :
        ShapeObject<ns::LineShape>(xml_node, color),
        points(stringToPoints(xml_node.child("polyline").attribute("points").as_string()))
{
    for (auto& point : points)
        m_shape.addPoint(point);
}

PolygonObject::PolygonObject(const pugi::xml_node& xml_node, const sf::Color& color) :
        ShapeObject<sf::ConvexShape>(xml_node, color),
        points(stringToPoints(xml_node.child("polygon").attribute("points").as_string()))
{
    m_shape.setPointCount(points.size());
    for (unsigned i = 0; i < points.size(); ++i)
        m_shape.setPoint(i, points[i]);
}

auto stringToPoints(const char* points_str) -> std::vector<sf::Vector2f> {
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
