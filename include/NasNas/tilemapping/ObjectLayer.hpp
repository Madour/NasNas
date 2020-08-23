/**
* Created by Modar Nasser on 22/08/2020.
**/

#pragma once

#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/tilemapping/Layer.hpp"
#include "NasNas/core/Logger.hpp"

namespace ns::tm {

    class ObjectLayer : public Layer {
        template <typename T>
        class Object : public PropertiesContainer {
        public:
            explicit Object(const pugi::xml_node& xml_node, const sf::Color& color);
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
        auto getPolygons() -> std::vector<Object<sf::ConvexShape>>&;

        auto getGlobalBounds() -> ns::FloatRect override;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Color m_color = sf::Color(180, 180, 180);
        std::vector<Object<sf::RectangleShape>> m_rectangles;
        std::vector<Object<sf::RectangleShape>> m_points;
        std::vector<Object<sf::CircleShape>> m_ellipses;
        std::vector<Object<sf::ConvexShape>> m_polygons;
    };

    template <typename T>
    ns::tm::ObjectLayer::Object<T>::Object(unsigned int id, float x, float y) :
    PropertiesContainer(){
        m_id = id;
        m_shape.setPosition(x, y);
    }

    template <typename T>
    auto ns::tm::ObjectLayer::Object<T>::getShape() const -> const T& {
        return m_shape;
    }

}
