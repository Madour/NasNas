/**
* Created by Modar Nasser on 22/08/2020.
**/

#pragma once

#include "NasNas/data/Shapes.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/tilemapping/Layer.hpp"

namespace ns::tm {

    class ObjectLayer : public Layer {

        template <typename T>
        class Object : public PropertiesContainer {
        public:
            explicit Object(const pugi::xml_node& xml_node, const sf::Color& color);
            auto getId() const -> unsigned int;
            auto getShape() const -> const T&;

        private:
            Object(unsigned int id, float x, float y);
            unsigned int m_id;
            T m_shape;
        };

    public:
        ObjectLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap);

        auto getRectangles() -> std::vector<Object<sf::RectangleShape>>&;
        auto getPoints() -> std::vector<Object<sf::RectangleShape>>&;
        auto getEllipses() -> std::vector<Object<sf::EllipseShape>>&;
        auto getPolygons() -> std::vector<Object<sf::ConvexShape>>&;
        auto getPolylines() -> std::vector<Object<sf::LineShape>>&;

        auto getRectangle(unsigned int id) -> const Object<sf::RectangleShape>&;
        auto getPoint(unsigned int id) -> const Object<sf::RectangleShape>&;
        auto getEllipse(unsigned int id) -> const Object<sf::EllipseShape>&;
        auto getPolygon(unsigned int id) -> const Object<sf::ConvexShape>&;
        auto getPolyline(unsigned int id) -> const Object<sf::LineShape>&;

        auto getGlobalBounds() -> ns::FloatRect override;

    private:
        static auto stringToPoints(const char*) -> std::vector<sf::Vector2f>;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Color m_color = sf::Color(180, 180, 180);

        std::vector<Object<sf::RectangleShape>> m_rectangles;
        std::vector<Object<sf::RectangleShape>> m_points;
        std::vector<Object<sf::EllipseShape>> m_ellipses;
        std::vector<Object<sf::ConvexShape>> m_polygons;
        std::vector<Object<sf::LineShape>> m_polylines;
    };

    template <typename T>
    ns::tm::ObjectLayer::Object<T>::Object(unsigned int id, float x, float y) :
    PropertiesContainer(){
        m_id = id;
        m_shape.setPosition(x, y);
    }

    template <typename T>
    auto ns::tm::ObjectLayer::Object<T>::getId() const -> unsigned int {
        return m_id;
    }

    template <typename T>
    auto ns::tm::ObjectLayer::Object<T>::getShape() const -> const T& {
        return m_shape;
    }

}
