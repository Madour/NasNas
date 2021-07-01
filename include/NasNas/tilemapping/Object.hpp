// Created by Modar Nasser on 28/06/2021.

#pragma once

#include "NasNas/core/graphics/Shapes.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"

namespace ns::tm {

    class PointObject;
    class RectangleObject;
    class EllipseObject;
    class PolylineObject;
    class PolygonObject;

    struct Object : PropertiesContainer {
        enum class Shape {
            Point,
            Rectangle,
            Ellipse,
            Polyline,
            Polygon
        };
        explicit Object(const pugi::xml_node& xml_node, Shape shape);
        virtual ~Object() = default;
        const unsigned id;
        const std::string name;
        const std::string type;
        const float x;
        const float y;
        const float rotation;
        const Shape shapetype;
        auto asPoint() -> PointObject&;
        auto asRectangle() -> RectangleObject&;
        auto asEllipse() -> EllipseObject&;
        auto asPolyline() -> PolylineObject&;
        auto asPolygon() -> PolygonObject&;
    };

    template <typename T>
    struct ShapeObject : Object {
        ShapeObject(const pugi::xml_node& xml_node, const sf::Color& color);
        auto getShape() const -> const T&;
    protected:
        T m_shape;
    private:
        Shape getShapeTypeEnum();
        using Object::asPoint;
        using Object::asRectangle;
        using Object::asEllipse;
        using Object::asPolyline;
        using Object::asPolygon;
    };

    struct PointObject : ShapeObject<sf::CircleShape> {
        PointObject(const pugi::xml_node& xml_node, const sf::Color& color);
    };

    struct RectangleObject : ShapeObject<sf::RectangleShape> {
        RectangleObject(const pugi::xml_node& xml_node, const sf::Color& color);
        const float width;
        const float height;
    };

    struct EllipseObject : ShapeObject<ns::EllipseShape> {
        EllipseObject(const pugi::xml_node& xml_node, const sf::Color& color);
        const float width;
        const float height;
    };

    struct PolylineObject : ShapeObject<ns::LineShape> {
        PolylineObject(const pugi::xml_node& xml_node, const sf::Color& color);
        const std::vector<sf::Vector2f> points;
    };

    struct PolygonObject : ShapeObject<sf::ConvexShape> {
        PolygonObject(const pugi::xml_node& xml_node, const sf::Color& color);
        const std::vector<sf::Vector2f> points;
    };

    template <typename T>
    ShapeObject<T>::ShapeObject(const pugi::xml_node& xml_node, const sf::Color& color) :
    Object(xml_node, getShapeTypeEnum())
    {
        m_shape.setPosition(x, y);
        m_shape.setRotation(rotation);

        if constexpr(std::is_same_v<T, ns::LineShape>) {
            m_shape.setColor({color.r, color.g, color.b, 200});
        }
        else {
            m_shape.setFillColor({color.r, color.g, color.b, 40});
            m_shape.setOutlineColor({color.r, color.g, color.b, 200});
            m_shape.setOutlineThickness(-1);
        }
    }

    template <typename T>
    auto ShapeObject<T>::getShape() const -> const T& {
        return m_shape;
    }

    template <typename T>
    auto ShapeObject<T>::getShapeTypeEnum() -> Shape {
        if constexpr(std::is_same_v<T, sf::CircleShape>)
            return Object::Shape::Point;
        else if constexpr(std::is_same_v<T, sf::RectangleShape>)
            return Object::Shape::Rectangle;
        else if constexpr(std::is_same_v<T, ns::EllipseShape>)
            return Object::Shape::Ellipse;
        else if constexpr(std::is_same_v<T, ns::LineShape>)
            return Object::Shape::Polyline;
        else if constexpr(std::is_same_v<T, sf::ConvexShape>)
            return Object::Shape::Polygon;
    }
}
