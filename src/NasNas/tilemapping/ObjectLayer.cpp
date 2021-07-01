/**
* Created by Modar Nasser on 22/08/2020.
**/

#include "NasNas/tilemapping/ObjectLayer.hpp"
#include "NasNas/tilemapping/TiledMap.hpp"

using namespace ns;
using namespace ns::tm;

ns::tm::ObjectLayer::ObjectLayer(const pugi::xml_node& xml_node, tm::TiledMap* tiledmap) :
Layer(xml_node, tiledmap) {
    if (xml_node.attribute("color"))
        m_color = hexToColor(std::string(xml_node.attribute("color").as_string()));
    for (const auto& xml_object : xml_node.children("object")) {
        if(xml_object.child("ellipse")) {
            m_ellipses.emplace_back(xml_object, m_color);
            m_objects.emplace_back(m_ellipses.back());
        }
        else if(xml_object.child("polyline")) {
            m_polylines.emplace_back(xml_object, m_color);
            m_objects.emplace_back(m_polylines.back());
        }
        else if(xml_object.child("polygon")) {
            m_polygons.emplace_back(xml_object, m_color);
            m_objects.emplace_back(m_polygons.back());
        }
        else if(xml_object.attribute("gid")) {
            // not yet implemented
        }
        else if (xml_object.child("point")) {
            m_points.emplace_back(xml_object, m_color);
            m_objects.emplace_back(m_points.back());
        }
        else {
            m_rectangles.emplace_back(xml_object, m_color);
            m_objects.emplace_back(m_rectangles.back());
        }
    }

    for (Object& object : m_objects) {
        if (!object.type.empty()) {
            m_objects_by_type[object.type].emplace_back(object);
        }
        if (!object.name.empty()) {
            m_objects_by_name[object.name].emplace_back(object);
        }
    }
}

auto ObjectLayer::getObjectsWithType(const std::string& type) const -> const std::vector<std::reference_wrapper<Object>>& {
    if (m_objects_by_type.count(type) > 0)
        return m_objects_by_type.at(type);
    return m_empty_object_vector;
}

auto ObjectLayer::getObjectsWithName(const std::string& name) const -> const std::vector<std::reference_wrapper<Object>>& {
    if (m_objects_by_name.count(name) > 0)
        return m_objects_by_name.at(name);
    return m_empty_object_vector;
}

auto ObjectLayer::allPoints() const -> const std::vector<PointObject>& {
    return m_points;
}

auto ObjectLayer::allRectangles() const -> const std::vector<RectangleObject>& {
    return m_rectangles;
}

auto ObjectLayer::allEllipses() const -> const std::vector<EllipseObject>& {
    return m_ellipses;
}

auto ObjectLayer::allPolygons() const -> const std::vector<PolygonObject>& {
    return m_polygons;
}

auto ObjectLayer::allPolylines() const -> const std::vector<PolylineObject>& {
    return m_polylines;
}


auto ObjectLayer::getRectangle(unsigned int id) const -> const RectangleObject& {
    for (auto& object : m_rectangles) {
        if (object.id == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Rectangle object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getPoint(unsigned int id) const -> const PointObject& {
    for (auto& object : m_points) {
        if (object.id == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Point object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getEllipse(unsigned int id) const -> const EllipseObject& {
    for (auto& object : m_ellipses) {
        if (object.id == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Ellipse object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getPolygon(unsigned int id) const -> const PolygonObject& {
    for (auto& object : m_polygons) {
        if (object.id == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Polygon object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getPolyline(unsigned int id) const -> const PolylineObject& {
    for (auto& object : m_polylines) {
        if (object.id == id) return object;
    }
    std::cout << "ObjectLayer «" << getName() << "» does not have a Polyline object id " << id << "." << std::endl;
    std::exit(-1);
}

auto ObjectLayer::getGlobalBounds() const -> ns::FloatRect {
    return {m_transformable.getPosition(), sf::Vector2f(m_tiledmap.getSize())};
}

void ObjectLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& point : m_points)
        target.draw(point.getShape(), states);

    for (const auto& rect : m_rectangles)
        target.draw(rect.getShape(), states);

    for (const auto& ellipse : m_ellipses)
        target.draw(ellipse.getShape(), states);

    for (const auto& polyline : m_polylines)
        target.draw(polyline.getShape(), states);

    for (const auto& polygon : m_polygons)
        target.draw(polygon.getShape(), states);
}
