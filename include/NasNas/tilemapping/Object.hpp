// Created by Modar Nasser on 28/06/2021.

#pragma once

#include "NasNas/core/graphics/Shapes.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"

namespace ns::tm {

    struct Object : PropertiesContainer {
        explicit Object(const pugi::xml_node& xml_node);
        const unsigned id;
        const std::string name;
        const std::string type;
        const float x;
        const float y;
        const float rotation;
    };

    template <typename T>
    struct ShapeObject : Object {
        ShapeObject(const pugi::xml_node& xml_node, const sf::Color& color);
        auto getShape() const -> const T&;
    protected:
        T m_shape;
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
    Object(xml_node)
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
}
