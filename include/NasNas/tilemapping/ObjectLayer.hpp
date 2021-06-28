/**
* Created by Modar Nasser on 22/08/2020.
**/

#pragma once

#include "NasNas/core/graphics/Shapes.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/tilemapping/Layer.hpp"
#include "NasNas/tilemapping/Object.hpp"

namespace ns::tm {

    class ObjectLayer : public Layer {
    public:
        ObjectLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap);

        auto allPoints() const -> const std::vector<PointObject>&;
        auto allRectangles() const -> const std::vector<RectangleObject>&;
        auto allEllipses() const -> const std::vector<EllipseObject>&;
        auto allPolylines() const -> const std::vector<PolylineObject>&;
        auto allPolygons() const -> const std::vector<PolygonObject>&;

        auto getPoint(unsigned int id) const -> const PointObject&;
        auto getRectangle(unsigned int id) const -> const RectangleObject&;
        auto getEllipse(unsigned int id) const -> const EllipseObject&;
        auto getPolyline(unsigned int id) const -> const PolylineObject&;
        auto getPolygon(unsigned int id) const -> const PolygonObject&;

        auto getGlobalBounds() const -> ns::FloatRect override;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Color m_color = sf::Color(180, 180, 180);

        std::vector<PointObject> m_points;
        std::vector<RectangleObject> m_rectangles;
        std::vector<EllipseObject> m_ellipses;
        std::vector<PolylineObject> m_polylines;
        std::vector<PolygonObject> m_polygons;
    };

}
